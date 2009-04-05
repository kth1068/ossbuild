/* Generic video mixer plugin
 * Copyright (C) 2004 Wim Taymans <wim@fluendo.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/**
 * SECTION:element-videomixer
 *
 * Videomixer can only accept AYUV video streams. For each of the requested
 * sink pads it will compare the incoming geometry and framerate to define the
 * output parameters. Indeed output video frames will have the geometry of the
 * biggest incoming video stream and the framerate of the fastest incoming one.
 *
 * Individual parameters for each input stream can be configured on the
 * #GstVideoMixerPad.
 *
 * <refsect2>
 * <title>Sample pipelines</title>
 * |[
 * gst-launch videotestsrc pattern=1 ! video/x-raw-yuv, framerate=\(fraction\)10/1, width=100, height=100 ! videobox border-alpha=0 alpha=0.5 top=-70 bottom=-70 right=-220 ! videomixer name=mix ! ffmpegcolorspace ! xvimagesink videotestsrc ! video/x-raw-yuv, framerate=\(fraction\)5/1, width=320, height=240 ! alpha alpha=0.7 ! mix.
 * ]| A pipeline to demonstrate videomixer used together with videobox.
 * This should show a 320x240 pixels video test source with some transparency
 * showing the background checker pattern. Another video test source with just
 * the snow pattern of 100x100 pixels is overlayed on top of the first one on
 * the left vertically centered with a small transparency showing the first
 * video test source behind and the checker pattern under it. Note that the
 * framerate of the output video is 10 frames per second.
 * </refsect2>
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gst/gst.h>
#include <gst/base/gstcollectpads.h>
#include <gst/controller/gstcontroller.h>

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include "videomixer.h"

GST_DEBUG_CATEGORY_STATIC (gst_videomixer_debug);
#define GST_CAT_DEFAULT gst_videomixer_debug

#define GST_VIDEO_MIXER_GET_STATE_LOCK(mix) \
  (GST_VIDEO_MIXER(mix)->state_lock)
#define GST_VIDEO_MIXER_STATE_LOCK(mix) \
  (g_mutex_lock(GST_VIDEO_MIXER_GET_STATE_LOCK (mix)))
#define GST_VIDEO_MIXER_STATE_UNLOCK(mix) \
  (g_mutex_unlock(GST_VIDEO_MIXER_GET_STATE_LOCK (mix)))

static GType gst_videomixer_get_type (void);


static void gst_videomixer_pad_class_init (GstVideoMixerPadClass * klass);

static void gst_videomixer_pad_init (GstVideoMixerPad * mixerpad);

static void gst_videomixer_pad_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec);
static void gst_videomixer_pad_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec);

static gboolean gst_videomixer_src_event (GstPad * pad, GstEvent * event);

static gboolean gst_videomixer_sink_event (GstPad * pad, GstEvent * event);


static void gst_videomixer_sort_pads (GstVideoMixer * mix);

#define DEFAULT_PAD_ZORDER 0
#define DEFAULT_PAD_XPOS   0
#define DEFAULT_PAD_YPOS   0
#define DEFAULT_PAD_ALPHA  1.0
enum
{
  ARG_PAD_0,
  ARG_PAD_ZORDER,
  ARG_PAD_XPOS,
  ARG_PAD_YPOS,
  ARG_PAD_ALPHA
};

static GType
gst_videomixer_pad_get_type (void)
{
  static GType videomixer_pad_type = 0;

  if (!videomixer_pad_type) {
    static const GTypeInfo videomixer_pad_info = {
      sizeof (GstVideoMixerPadClass),
      NULL,
      NULL,
      (GClassInitFunc) gst_videomixer_pad_class_init,
      NULL,
      NULL,
      sizeof (GstVideoMixerPad),
      0,
      (GInstanceInitFunc) gst_videomixer_pad_init,
    };

    videomixer_pad_type = g_type_register_static (GST_TYPE_PAD,
        "GstVideoMixerPad", &videomixer_pad_info, 0);
  }
  return videomixer_pad_type;
}

static void
gst_videomixer_pad_class_init (GstVideoMixerPadClass * klass)
{
  GObjectClass *gobject_class;

  gobject_class = (GObjectClass *) klass;

  gobject_class->set_property =
      GST_DEBUG_FUNCPTR (gst_videomixer_pad_set_property);
  gobject_class->get_property =
      GST_DEBUG_FUNCPTR (gst_videomixer_pad_get_property);

  g_object_class_install_property (gobject_class, ARG_PAD_ZORDER,
      g_param_spec_uint ("zorder", "Z-Order", "Z Order of the picture",
          0, 10000, DEFAULT_PAD_ZORDER,
          G_PARAM_READWRITE | GST_PARAM_CONTROLLABLE));
  g_object_class_install_property (gobject_class, ARG_PAD_XPOS,
      g_param_spec_int ("xpos", "X Position", "X Position of the picture",
          G_MININT, G_MAXINT, DEFAULT_PAD_XPOS,
          G_PARAM_READWRITE | GST_PARAM_CONTROLLABLE));
  g_object_class_install_property (gobject_class, ARG_PAD_YPOS,
      g_param_spec_int ("ypos", "Y Position", "Y Position of the picture",
          G_MININT, G_MAXINT, DEFAULT_PAD_YPOS,
          G_PARAM_READWRITE | GST_PARAM_CONTROLLABLE));
  g_object_class_install_property (gobject_class, ARG_PAD_ALPHA,
      g_param_spec_double ("alpha", "Alpha", "Alpha of the picture", 0.0, 1.0,
          DEFAULT_PAD_ALPHA, G_PARAM_READWRITE | GST_PARAM_CONTROLLABLE));
}

static void
gst_videomixer_pad_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstVideoMixerPad *pad = GST_VIDEO_MIXER_PAD (object);

  switch (prop_id) {
    case ARG_PAD_ZORDER:
      g_value_set_uint (value, pad->zorder);
      break;
    case ARG_PAD_XPOS:
      g_value_set_int (value, pad->xpos);
      break;
    case ARG_PAD_YPOS:
      g_value_set_int (value, pad->ypos);
      break;
    case ARG_PAD_ALPHA:
      g_value_set_double (value, pad->alpha);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_videomixer_pad_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstVideoMixerPad *pad;

  GstVideoMixer *mix;

  pad = GST_VIDEO_MIXER_PAD (object);
  mix = GST_VIDEO_MIXER (gst_pad_get_parent (GST_PAD (pad)));

  switch (prop_id) {
    case ARG_PAD_ZORDER:
      GST_VIDEO_MIXER_STATE_LOCK (mix);
      pad->zorder = g_value_get_uint (value);
      gst_videomixer_sort_pads (mix);
      GST_VIDEO_MIXER_STATE_UNLOCK (mix);
      break;
    case ARG_PAD_XPOS:
      pad->xpos = g_value_get_int (value);
      break;
    case ARG_PAD_YPOS:
      pad->ypos = g_value_get_int (value);
      break;
    case ARG_PAD_ALPHA:
      pad->alpha = g_value_get_double (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }

  gst_object_unref (mix);
}

static void
gst_videomixer_set_master_geometry (GstVideoMixer * mix)
{
  GSList *walk;

  gint width = 0, height = 0, fps_n = 0, fps_d = 0;

  GstVideoMixerPad *master = NULL;

  walk = mix->sinkpads;
  while (walk) {
    GstVideoMixerPad *mixpad = GST_VIDEO_MIXER_PAD (walk->data);

    walk = g_slist_next (walk);

    /* Biggest input geometry will be our output geometry */
    width = MAX (width, mixpad->in_width);
    height = MAX (height, mixpad->in_height);

    /* If mix framerate < mixpad framerate, using fractions */
    GST_DEBUG_OBJECT (mix, "comparing framerate %d/%d to mixpad's %d/%d",
        fps_n, fps_d, mixpad->fps_n, mixpad->fps_d);
    if ((!fps_n && !fps_d) ||
        ((gint64) fps_n * mixpad->fps_d < (gint64) mixpad->fps_n * fps_d)) {
      fps_n = mixpad->fps_n;
      fps_d = mixpad->fps_d;
      GST_DEBUG_OBJECT (mixpad, "becomes the master pad");
      master = mixpad;
    }
  }

  /* set results */
  if (mix->master != master || mix->in_width != width
      || mix->in_height != height || mix->fps_n != fps_n
      || mix->fps_d != fps_d) {
    mix->setcaps = TRUE;
    mix->sendseg = TRUE;
    mix->master = master;
    mix->in_width = width;
    mix->in_height = height;
    mix->fps_n = fps_n;
    mix->fps_d = fps_d;
  }
}

static gboolean
gst_videomixer_pad_sink_setcaps (GstPad * pad, GstCaps * vscaps)
{
  GstVideoMixer *mix;

  GstVideoMixerPad *mixpad;

  GstStructure *structure;

  gint in_width, in_height;

  gboolean ret = FALSE;

  const GValue *framerate;

  mix = GST_VIDEO_MIXER (gst_pad_get_parent (pad));
  mixpad = GST_VIDEO_MIXER_PAD (pad);

  if (!mixpad)
    goto beach;

  GST_DEBUG_OBJECT (mixpad, "setcaps triggered");

  structure = gst_caps_get_structure (vscaps, 0);

  if (!gst_structure_get_int (structure, "width", &in_width)
      || !gst_structure_get_int (structure, "height", &in_height)
      || (framerate = gst_structure_get_value (structure, "framerate")) == NULL)
    goto beach;

  GST_VIDEO_MIXER_STATE_LOCK (mix);
  mixpad->fps_n = gst_value_get_fraction_numerator (framerate);
  mixpad->fps_d = gst_value_get_fraction_denominator (framerate);

  mixpad->in_width = in_width;
  mixpad->in_height = in_height;

  gst_videomixer_set_master_geometry (mix);
  GST_VIDEO_MIXER_STATE_UNLOCK (mix);

  ret = TRUE;

beach:
  gst_object_unref (mix);

  return ret;
}

static void
gst_videomixer_pad_link (GstPad * pad, GstPad * peer, gpointer data)
{
  GST_DEBUG_OBJECT (pad, "connected");
}

static void
gst_videomixer_pad_unlink (GstPad * pad, GstPad * peer, gpointer data)
{
  GST_DEBUG_OBJECT (pad, "unlinked");
}

static void
gst_videomixer_pad_init (GstVideoMixerPad * mixerpad)
{
  g_signal_connect (mixerpad, "linked",
      G_CALLBACK (gst_videomixer_pad_link), mixerpad);
  g_signal_connect (mixerpad, "unlinked",
      G_CALLBACK (gst_videomixer_pad_unlink), mixerpad);

  /* setup some pad functions */
  gst_pad_set_setcaps_function (GST_PAD (mixerpad),
      gst_videomixer_pad_sink_setcaps);

  mixerpad->zorder = DEFAULT_PAD_ZORDER;
  mixerpad->xpos = DEFAULT_PAD_XPOS;
  mixerpad->ypos = DEFAULT_PAD_YPOS;
  mixerpad->alpha = DEFAULT_PAD_ALPHA;
}


/* elementfactory information */
static const GstElementDetails gst_videomixer_details =
GST_ELEMENT_DETAILS ("Video mixer",
    "Filter/Editor/Video",
    "Mix multiple video streams",
    "Wim Taymans <wim@fluendo.com>");

/* VideoMixer signals and args */
enum
{
  /* FILL ME */
  LAST_SIGNAL
};

#define DEFAULT_BACKGROUND VIDEO_MIXER_BACKGROUND_CHECKER
enum
{
  ARG_0,
  ARG_BACKGROUND
};

#define GST_TYPE_VIDEO_MIXER_BACKGROUND (gst_video_mixer_background_get_type())
static GType
gst_video_mixer_background_get_type (void)
{
  static GType video_mixer_background_type = 0;

  static const GEnumValue video_mixer_background[] = {
    {VIDEO_MIXER_BACKGROUND_CHECKER, "Checker pattern", "checker"},
    {VIDEO_MIXER_BACKGROUND_BLACK, "Black", "black"},
    {VIDEO_MIXER_BACKGROUND_WHITE, "White", "white"},
    {0, NULL, NULL},
  };

  if (!video_mixer_background_type) {
    video_mixer_background_type =
        g_enum_register_static ("GstVideoMixerBackground",
        video_mixer_background);
  }
  return video_mixer_background_type;
}

static GstStaticPadTemplate src_factory = GST_STATIC_PAD_TEMPLATE ("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("video/x-raw-yuv,"
        "format = (fourcc) AYUV,"
        "width = (int) [ 1, max ],"
        "height = (int) [ 1, max ]," "framerate = (fraction) [ 0/1, MAX ]")
    );

static GstStaticPadTemplate sink_factory = GST_STATIC_PAD_TEMPLATE ("sink_%d",
    GST_PAD_SINK,
    GST_PAD_REQUEST,
    GST_STATIC_CAPS ("video/x-raw-yuv,"
        "format = (fourcc) AYUV,"
        "width = (int) [ 1, max ],"
        "height = (int) [ 1, max ]," "framerate = (fraction) [ 0/1, MAX ]")
    );

static void gst_videomixer_finalize (GObject * object);

static GstCaps *gst_videomixer_getcaps (GstPad * pad);

static gboolean gst_videomixer_query (GstPad * pad, GstQuery * query);

static GstFlowReturn gst_videomixer_collected (GstCollectPads * pads,
    GstVideoMixer * mix);
static GstPad *gst_videomixer_request_new_pad (GstElement * element,
    GstPadTemplate * templ, const gchar * name);
static void gst_videomixer_release_pad (GstElement * element, GstPad * pad);

static void gst_videomixer_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec);
static void gst_videomixer_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec);
static GstStateChangeReturn gst_videomixer_change_state (GstElement * element,
    GstStateChange transition);

/*static guint gst_videomixer_signals[LAST_SIGNAL] = { 0 }; */

static void gst_videomixer_child_proxy_init (gpointer g_iface,
    gpointer iface_data);
static void _do_init (GType object_type);

GST_BOILERPLATE_FULL (GstVideoMixer, gst_videomixer, GstElement,
    GST_TYPE_ELEMENT, _do_init);

static void
_do_init (GType object_type)
{
  const GInterfaceInfo child_proxy_info = {
    (GInterfaceInitFunc) gst_videomixer_child_proxy_init,
    NULL,
    NULL
  };
  g_type_add_interface_static (object_type, GST_TYPE_CHILD_PROXY,
      &child_proxy_info);
  GST_INFO ("GstChildProxy interface registered");
}

static GstObject *
gst_videomixer_child_proxy_get_child_by_index (GstChildProxy * child_proxy,
    guint index)
{
  GstVideoMixer *mix = GST_VIDEO_MIXER (child_proxy);

  GstObject *obj;

  GST_VIDEO_MIXER_STATE_LOCK (mix);
  if ((obj = g_slist_nth_data (mix->sinkpads, index)))
    gst_object_ref (obj);
  GST_VIDEO_MIXER_STATE_UNLOCK (mix);
  return obj;
}

static guint
gst_videomixer_child_proxy_get_children_count (GstChildProxy * child_proxy)
{
  guint count = 0;

  GstVideoMixer *mix = GST_VIDEO_MIXER (child_proxy);

  GST_VIDEO_MIXER_STATE_LOCK (mix);
  count = mix->numpads;
  GST_VIDEO_MIXER_STATE_UNLOCK (mix);
  GST_INFO ("Children Count: %d", count);
  return count;
}

static void
gst_videomixer_child_proxy_init (gpointer g_iface, gpointer iface_data)
{
  GstChildProxyInterface *iface = g_iface;

  GST_INFO ("intializing child proxy interface");
  iface->get_child_by_index = gst_videomixer_child_proxy_get_child_by_index;
  iface->get_children_count = gst_videomixer_child_proxy_get_children_count;
}

static void
gst_videomixer_base_init (gpointer g_class)
{
  GstElementClass *element_class = GST_ELEMENT_CLASS (g_class);

  gst_element_class_add_pad_template (element_class,
      gst_static_pad_template_get (&src_factory));
  gst_element_class_add_pad_template (element_class,
      gst_static_pad_template_get (&sink_factory));

  gst_element_class_set_details (element_class, &gst_videomixer_details);
}

static void
gst_videomixer_class_init (GstVideoMixerClass * klass)
{
  GObjectClass *gobject_class;

  GstElementClass *gstelement_class;

  gobject_class = (GObjectClass *) klass;
  gstelement_class = (GstElementClass *) klass;

  parent_class = g_type_class_peek_parent (klass);

  gobject_class->finalize = GST_DEBUG_FUNCPTR (gst_videomixer_finalize);

  gobject_class->get_property = gst_videomixer_get_property;
  gobject_class->set_property = gst_videomixer_set_property;

  g_object_class_install_property (gobject_class, ARG_BACKGROUND,
      g_param_spec_enum ("background", "Background", "Background type",
          GST_TYPE_VIDEO_MIXER_BACKGROUND,
          DEFAULT_BACKGROUND, G_PARAM_READWRITE));

  gstelement_class->request_new_pad =
      GST_DEBUG_FUNCPTR (gst_videomixer_request_new_pad);
  gstelement_class->release_pad =
      GST_DEBUG_FUNCPTR (gst_videomixer_release_pad);
  gstelement_class->change_state =
      GST_DEBUG_FUNCPTR (gst_videomixer_change_state);

  /* Register the pad class */
  (void) (GST_TYPE_VIDEO_MIXER_PAD);
}

static void
gst_videomixer_collect_free (GstVideoMixerCollect * mixcol)
{
  if (mixcol->buffer) {
    gst_buffer_unref (mixcol->buffer);
    mixcol->buffer = NULL;
  }
}

static void
gst_videomixer_reset (GstVideoMixer * mix)
{
  GSList *walk;

  mix->in_width = 0;
  mix->in_height = 0;
  mix->out_width = 0;
  mix->out_height = 0;
  mix->fps_n = mix->fps_d = 0;
  mix->setcaps = FALSE;
  mix->sendseg = FALSE;
  mix->segment_position = 0;
  mix->segment_rate = 1.0;

  mix->last_ts = 0;

  /* clean up collect data */
  walk = mix->collect->data;
  while (walk) {
    GstVideoMixerCollect *data = (GstVideoMixerCollect *) walk->data;

    gst_videomixer_collect_free (data);
    walk = g_slist_next (walk);
  }

  mix->next_sinkpad = 0;
}

static void
gst_videomixer_init (GstVideoMixer * mix, GstVideoMixerClass * g_class)
{
  GstElementClass *klass = GST_ELEMENT_GET_CLASS (mix);

  mix->srcpad =
      gst_pad_new_from_template (gst_element_class_get_pad_template (klass,
          "src"), "src");
  gst_pad_set_getcaps_function (GST_PAD (mix->srcpad),
      GST_DEBUG_FUNCPTR (gst_videomixer_getcaps));
  gst_pad_set_query_function (GST_PAD (mix->srcpad),
      GST_DEBUG_FUNCPTR (gst_videomixer_query));
  gst_pad_set_event_function (GST_PAD (mix->srcpad),
      GST_DEBUG_FUNCPTR (gst_videomixer_src_event));
  gst_element_add_pad (GST_ELEMENT (mix), mix->srcpad);

  mix->collect = gst_collect_pads_new ();
  mix->background = DEFAULT_BACKGROUND;

  gst_collect_pads_set_function (mix->collect,
      (GstCollectPadsFunction) GST_DEBUG_FUNCPTR (gst_videomixer_collected),
      mix);

  mix->state_lock = g_mutex_new ();
  /* initialize variables */
  gst_videomixer_reset (mix);
}

static void
gst_videomixer_finalize (GObject * object)
{
  GstVideoMixer *mix = GST_VIDEO_MIXER (object);

  gst_object_unref (mix->collect);
  g_mutex_free (mix->state_lock);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

static gboolean
gst_videomixer_query_duration (GstVideoMixer * mix, GstQuery * query)
{
  gint64 max;

  gboolean res;

  GstFormat format;

  GstIterator *it;

  gboolean done;

  /* parse format */
  gst_query_parse_duration (query, &format, NULL);

  max = -1;
  res = TRUE;
  done = FALSE;

  /* Take maximum of all durations */
  it = gst_element_iterate_sink_pads (GST_ELEMENT_CAST (mix));
  while (!done) {
    GstIteratorResult ires;

    gpointer item;

    ires = gst_iterator_next (it, &item);
    switch (ires) {
      case GST_ITERATOR_DONE:
        done = TRUE;
        break;
      case GST_ITERATOR_OK:
      {
        GstPad *pad = GST_PAD_CAST (item);

        gint64 duration;

        /* ask sink peer for duration */
        res &= gst_pad_query_peer_duration (pad, &format, &duration);
        /* take max from all valid return values */
        if (res) {
          /* valid unknown length, stop searching */
          if (duration == -1) {
            max = duration;
            done = TRUE;
          }
          /* else see if bigger than current max */
          else if (duration > max)
            max = duration;
        }
        gst_object_unref (pad);
        break;
      }
      case GST_ITERATOR_RESYNC:
        max = -1;
        res = TRUE;
        gst_iterator_resync (it);
        break;
      default:
        res = FALSE;
        done = TRUE;
        break;
    }
  }
  gst_iterator_free (it);

  if (res) {
    /* and store the max */
    GST_DEBUG_OBJECT (mix, "Total duration in format %s: %"
        GST_TIME_FORMAT, gst_format_get_name (format), GST_TIME_ARGS (max));
    gst_query_set_duration (query, format, max);
  }

  return res;
}

static gboolean
gst_videomixer_query_latency (GstVideoMixer * mix, GstQuery * query)
{
  GstClockTime min, max;

  gboolean live;

  gboolean res;

  GstIterator *it;

  gboolean done;

  res = TRUE;
  done = FALSE;

  live = FALSE;
  min = 0;
  max = GST_CLOCK_TIME_NONE;

  /* Take maximum of all latency values */
  it = gst_element_iterate_sink_pads (GST_ELEMENT_CAST (mix));
  while (!done) {
    GstIteratorResult ires;

    gpointer item;

    ires = gst_iterator_next (it, &item);
    switch (ires) {
      case GST_ITERATOR_DONE:
        done = TRUE;
        break;
      case GST_ITERATOR_OK:
      {
        GstPad *pad = GST_PAD_CAST (item);

        GstQuery *peerquery;

        GstClockTime min_cur, max_cur;

        gboolean live_cur;

        peerquery = gst_query_new_latency ();

        /* Ask peer for latency */
        res &= gst_pad_peer_query (pad, peerquery);

        /* take max from all valid return values */
        if (res) {
          gst_query_parse_latency (peerquery, &live_cur, &min_cur, &max_cur);

          if (min_cur > min)
            min = min_cur;

          if (max_cur != GST_CLOCK_TIME_NONE &&
              ((max != GST_CLOCK_TIME_NONE && max_cur > max) ||
                  (max == GST_CLOCK_TIME_NONE)))
            max = max_cur;

          live = live || live_cur;
        }

        gst_query_unref (peerquery);
        gst_object_unref (pad);
        break;
      }
      case GST_ITERATOR_RESYNC:
        live = FALSE;
        min = 0;
        max = GST_CLOCK_TIME_NONE;
        res = TRUE;
        gst_iterator_resync (it);
        break;
      default:
        res = FALSE;
        done = TRUE;
        break;
    }
  }
  gst_iterator_free (it);

  if (res) {
    /* store the results */
    GST_DEBUG_OBJECT (mix, "Calculated total latency: live %s, min %"
        GST_TIME_FORMAT ", max %" GST_TIME_FORMAT,
        (live ? "yes" : "no"), GST_TIME_ARGS (min), GST_TIME_ARGS (max));
    gst_query_set_latency (query, live, min, max);
  }

  return res;
}

static gboolean
gst_videomixer_query (GstPad * pad, GstQuery * query)
{
  GstVideoMixer *mix = GST_VIDEO_MIXER (gst_pad_get_parent (pad));

  gboolean res = FALSE;

  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_POSITION:
    {
      GstFormat format;

      gst_query_parse_position (query, &format, NULL);

      switch (format) {
        case GST_FORMAT_TIME:
          /* FIXME, bring to stream time, might be tricky */
          gst_query_set_position (query, format, mix->last_ts);
          res = TRUE;
          break;
        default:
          break;
      }
      break;
    }
    case GST_QUERY_DURATION:
      res = gst_videomixer_query_duration (mix, query);
      break;
    case GST_QUERY_LATENCY:
      res = gst_videomixer_query_latency (mix, query);
      break;
    default:
      /* FIXME, needs a custom query handler because we have multiple
       * sinkpads */
      res = gst_pad_query_default (pad, query);
      break;
  }

  gst_object_unref (mix);
  return res;
}

static GstCaps *
gst_videomixer_getcaps (GstPad * pad)
{
  GstVideoMixer *mix;

  GstCaps *caps;

  GstStructure *structure;

  mix = GST_VIDEO_MIXER (gst_pad_get_parent (pad));
  caps = gst_caps_copy (gst_pad_get_pad_template_caps (mix->srcpad));

  structure = gst_caps_get_structure (caps, 0);

  if (mix->out_width != 0) {
    gst_structure_set (structure, "width", G_TYPE_INT, mix->out_width, NULL);
  }
  if (mix->out_height != 0) {
    gst_structure_set (structure, "height", G_TYPE_INT, mix->out_height, NULL);
  }
  if (mix->fps_d != 0) {
    gst_structure_set (structure,
        "framerate", GST_TYPE_FRACTION, mix->fps_n, mix->fps_d, NULL);
  }

  gst_object_unref (mix);

  return caps;
}

static GstPad *
gst_videomixer_request_new_pad (GstElement * element,
    GstPadTemplate * templ, const gchar * req_name)
{
  GstVideoMixer *mix = NULL;

  GstVideoMixerPad *mixpad = NULL;

  GstElementClass *klass = GST_ELEMENT_GET_CLASS (element);

  g_return_val_if_fail (templ != NULL, NULL);

  if (templ->direction != GST_PAD_SINK) {
    g_warning ("videomixer: request pad that is not a SINK pad\n");
    return NULL;
  }

  g_return_val_if_fail (GST_IS_VIDEO_MIXER (element), NULL);

  mix = GST_VIDEO_MIXER (element);

  if (templ == gst_element_class_get_pad_template (klass, "sink_%d")) {
    gint serial = 0;

    gchar *name = NULL;

    GstVideoMixerCollect *mixcol = NULL;

    if (req_name == NULL || strlen (req_name) < 6) {
      /* no name given when requesting the pad, use next available int */
      serial = mix->next_sinkpad++;
    } else {
      /* parse serial number from requested padname */
      serial = atoi (&req_name[5]);
      if (serial >= mix->next_sinkpad)
        mix->next_sinkpad = serial + 1;
    }
    /* create new pad with the name */
    name = g_strdup_printf ("sink_%d", serial);
    mixpad = g_object_new (GST_TYPE_VIDEO_MIXER_PAD, "name", name, "direction",
        templ->direction, "template", templ, NULL);
    g_free (name);

    GST_VIDEO_MIXER_STATE_LOCK (mix);
    mixpad->zorder = mix->numpads;
    mixpad->xpos = DEFAULT_PAD_XPOS;
    mixpad->ypos = DEFAULT_PAD_YPOS;
    mixpad->alpha = DEFAULT_PAD_ALPHA;

    mixcol = (GstVideoMixerCollect *)
        gst_collect_pads_add_pad (mix->collect, GST_PAD (mixpad),
        sizeof (GstVideoMixerCollect));

    /* FIXME: hacked way to override/extend the event function of
     * GstCollectPads; because it sets its own event function giving the
     * element no access to events */
    mix->collect_event =
        (GstPadEventFunction) GST_PAD_EVENTFUNC (GST_PAD (mixpad));
    gst_pad_set_event_function (GST_PAD (mixpad),
        GST_DEBUG_FUNCPTR (gst_videomixer_sink_event));

    /* Keep track of each other */
    mixcol->mixpad = mixpad;
    mixpad->mixcol = mixcol;

    /* Keep an internal list of mixpads for zordering */
    mix->sinkpads = g_slist_append (mix->sinkpads, mixpad);
    mix->numpads++;
    GST_VIDEO_MIXER_STATE_UNLOCK (mix);
  } else {
    g_warning ("videomixer: this is not our template!\n");
    return NULL;
  }

  /* add the pad to the element */
  gst_element_add_pad (element, GST_PAD (mixpad));
  gst_child_proxy_child_added (GST_OBJECT (mix), GST_OBJECT (mixpad));

  return GST_PAD (mixpad);
}

static void
gst_videomixer_release_pad (GstElement * element, GstPad * pad)
{
  GstVideoMixer *mix = NULL;

  GstVideoMixerPad *mixpad;

  mix = GST_VIDEO_MIXER (element);
  GST_VIDEO_MIXER_STATE_LOCK (mix);
  if (G_UNLIKELY (g_slist_find (mix->sinkpads, pad) == NULL)) {
    g_warning ("Unknown pad %s", GST_PAD_NAME (pad));
    goto error;
  }

  mixpad = GST_VIDEO_MIXER_PAD (pad);

  mix->sinkpads = g_slist_remove (mix->sinkpads, pad);
  gst_videomixer_collect_free (mixpad->mixcol);
  gst_collect_pads_remove_pad (mix->collect, pad);
  gst_child_proxy_child_removed (GST_OBJECT (mix), GST_OBJECT (mixpad));
  /* determine possibly new geometry and master */
  gst_videomixer_set_master_geometry (mix);
  mix->numpads--;
  GST_VIDEO_MIXER_STATE_UNLOCK (mix);

  gst_element_remove_pad (element, pad);
  return;
error:
  GST_VIDEO_MIXER_STATE_UNLOCK (mix);
}

#define BLEND_NORMAL(Y1,U1,V1,Y2,U2,V2,alpha,Y,U,V)     \
        Y = ((Y1*(255-alpha))+(Y2*alpha))>>8;           \
        U = ((U1*(255-alpha))+(U2*alpha))>>8;           \
        V = ((V1*(255-alpha))+(V2*alpha))>>8;

#define BLEND_ADD(Y1,U1,V1,Y2,U2,V2,alpha,Y,U,V)                \
        Y = Y1+((Y2*alpha)>>8);                                 \
        U = U1+(((127*(255-alpha)+(U2*alpha)))>>8)-127;         \
        V = V1+(((127*(255-alpha)+(V2*alpha)))>>8)-127;         \
        if (Y>255) {                                            \
          gint mult = MAX (0, 288-Y);                           \
          U = ((U*mult) + (127*(32-mult)))>>5;                  \
          V = ((V*mult) + (127*(32-mult)))>>5;                  \
          Y = 255;                                              \
        }                                                       \
        U = MIN (U,255);                                        \
        V = MIN (V,255);

#define BLEND_SUBTRACT(Y1,U1,V1,Y2,U2,V2,alpha,Y,U,V)           \
        Y = Y1-((Y2*alpha)>>8);                                 \
        U = U1+(((127*(255-alpha)+(U2*alpha)))>>8)-127;         \
        V = V1+(((127*(255-alpha)+(V2*alpha)))>>8)-127;         \
        if (Y<0) {                                              \
          gint mult = MIN (32, -Y);                             \
          U = ((U*(32-mult)) + (127*mult))>>5;                  \
          V = ((V*(32-mult)) + (127*mult))>>5;                  \
          Y = 0;                                                \
        }

#define BLEND_DARKEN(Y1,U1,V1,Y2,U2,V2,alpha,Y,U,V)     \
        if (Y1 < Y2) {                                  \
          Y = Y1; U = U1; V = V1;                       \
        }                                               \
        else {                                          \
          Y = ((Y1*(255-alpha))+(Y2*alpha))>>8;         \
          U = ((U1*(255-alpha))+(U2*alpha))>>8;         \
          V = ((V1*(255-alpha))+(V2*alpha))>>8;         \
        }

#define BLEND_LIGHTEN(Y1,U1,V1,Y2,U2,V2,alpha,Y,U,V)    \
        if (Y1 > Y2) {                                  \
          Y = Y1; U = U1; V = V1;                       \
        }                                               \
        else {                                          \
          Y = ((Y1*(255-alpha))+(Y2*alpha))>>8;         \
          U = ((U1*(255-alpha))+(U2*alpha))>>8;         \
          V = ((V1*(255-alpha))+(V2*alpha))>>8;         \
        }

#define BLEND_MULTIPLY(Y1,U1,V1,Y2,U2,V2,alpha,Y,U,V)                   \
        Y = (Y1*(256*(255-alpha) +(Y2*alpha)))>>16;                     \
        U = ((U1*(255-alpha)*256)+(alpha*(U1*Y2+128*(256-Y2))))>>16;    \
        V = ((V1*(255-alpha)*256)+(alpha*(V1*Y2+128*(256-Y2))))>>16;

#define BLEND_DIFFERENCE(Y1,U1,V1,Y2,U2,V2,alpha,Y,U,V)         \
        Y = ABS((gint)Y1-(gint)Y2)+127;                         \
        U = ABS((gint)U1-(gint)U2)+127;                         \
        V = ABS((gint)V1-(gint)V2)+127;                         \
        Y = ((Y*alpha)+(Y1*(255-alpha)))>>8;                    \
        U = ((U*alpha)+(U1*(255-alpha)))>>8;                    \
        V = ((V*alpha)+(V1*(255-alpha)))>>8;                    \
        if (Y>255) {                                            \
          gint mult = MAX (0, 288-Y);                           \
          U = ((U*mult) + (127*(32-mult)))>>5;                  \
          V = ((V*mult) + (127*(32-mult)))>>5;                  \
          Y = 255;                                              \
        } else if (Y<0) {                                       \
          gint mult = MIN (32, -Y);                             \
          U = ((U*(32-mult)) + (127*mult))>>5;                  \
          V = ((V*(32-mult)) + (127*mult))>>5;                  \
          Y = 0;                                                \
        }                                                       \
        U = CLAMP(U, 0, 255);                                   \
        V = CLAMP(V, 0, 255);

#define BLEND_EXCLUSION(Y1,U1,V1,Y2,U2,V2,alpha,Y,U,V)          \
        Y = ((gint)(Y1^0xff)*Y2+(gint)(Y2^0xff)*Y1)>>8;         \
        U = ((gint)(U1^0xff)*Y2+(gint)(Y2^0xff)*U1)>>8;         \
        V = ((gint)(V1^0xff)*Y2+(gint)(Y2^0xff)*V1)>>8;         \
        Y = ((Y*alpha)+(Y1*(255-alpha)))>>8;                    \
        U = ((U*alpha)+(U1*(255-alpha)))>>8;                    \
        V = ((V*alpha)+(V1*(255-alpha)))>>8;                    \
        if (Y>255) {                                            \
          gint mult = MAX (0, 288-Y);                           \
          U = ((U*mult) + (127*(32-mult)))>>5;                  \
          V = ((V*mult) + (127*(32-mult)))>>5;                  \
          Y = 255;                                              \
        } else if (Y<0) {                                       \
          gint mult = MIN (32, -Y);                             \
          U = ((U*(32-mult)) + (127*mult))>>5;                  \
          V = ((V*(32-mult)) + (127*mult))>>5;                  \
          Y = 0;                                                \
        }                                                       \
        U = CLAMP(U, 0, 255);                                   \
        V = CLAMP(V, 0, 255);

#define BLEND_SOFTLIGHT(Y1,U1,V1,Y2,U2,V2,alpha,Y,U,V)          \
        Y = (gint)Y1+(gint)Y2 - 127;                            \
        U = (gint)U1+(gint)U2 - 127;                            \
        V = (gint)V1+(gint)V2 - 127;                            \
        Y = ((Y*alpha)+(Y1*(255-alpha)))>>8;                    \
        U = ((U*alpha)+(U1*(255-alpha)))>>8;                    \
        V = ((V*alpha)+(V1*(255-alpha)))>>8;                    \
        if (Y>255) {                                            \
          gint mult = MAX (0, 288-Y);                           \
          U = ((U*mult) + (127*(32-mult)))>>5;                  \
          V = ((V*mult) + (127*(32-mult)))>>5;                  \
          Y = 255;                                              \
        } else if (Y<0) {                                       \
          gint mult = MIN (32, -Y);                             \
          U = ((U*(32-mult)) + (127*mult))>>5;                  \
          V = ((V*(32-mult)) + (127*mult))>>5;                  \
          Y = 0;                                                \
        }                                                       \

#define BLEND_HARDLIGHT(Y1,U1,V1,Y2,U2,V2,alpha,Y,U,V)          \
        Y = (gint)Y1+(gint)Y2*2 - 255;                          \
        U = (gint)U1+(gint)U2 - 127;                            \
        V = (gint)V1+(gint)V2 - 127;                            \
        Y = ((Y*alpha)+(Y1*(255-alpha)))>>8;                    \
        U = ((U*alpha)+(U1*(255-alpha)))>>8;                    \
        V = ((V*alpha)+(V1*(255-alpha)))>>8;                    \
        if (Y>255) {                                            \
          gint mult = MAX (0, 288-Y);                           \
          U = ((U*mult) + (127*(32-mult)))>>5;                  \
          V = ((V*mult) + (127*(32-mult)))>>5;                  \
          Y = 255;                                              \
        } else if (Y<0) {                                       \
          gint mult = MIN (32, -Y);                             \
          U = ((U*(32-mult)) + (127*mult))>>5;                  \
          V = ((V*(32-mult)) + (127*mult))>>5;                  \
          Y = 0;                                                \
        }                                                       \

#define BLEND_MODE BLEND_NORMAL
#if 0
#define BLEND_MODE BLEND_NORMAL
#define BLEND_MODE BLEND_ADD
#define BLEND_MODE BLEND_SUBTRACT
#define BLEND_MODE BLEND_LIGHTEN
#define BLEND_MODE BLEND_DARKEN
#define BLEND_MODE BLEND_MULTIPLY
#define BLEND_MODE BLEND_DIFFERENCE
#define BLEND_MODE BLEND_EXCLUSION
#define BLEND_MODE BLEND_SOFTLIGHT
#define BLEND_MODE BLEND_HARDLIGHT
#endif

/* note that this function does packing conversion and blending at the
 * same time */
static void
gst_videomixer_blend_ayuv_ayuv (guint8 * src, gint xpos, gint ypos,
    gint src_width, gint src_height, gdouble src_alpha,
    guint8 * dest, gint dest_width, gint dest_height)
{
  gint alpha, b_alpha;

  gint i, j;

  gint src_stride, dest_stride;

  gint src_add, dest_add;

  gint Y, U, V;

  src_stride = src_width * 4;
  dest_stride = dest_width * 4;

  b_alpha = (gint) (src_alpha * 255);

  /* adjust src pointers for negative sizes */
  if (xpos < 0) {
    src += -xpos * 4;
    src_width -= -xpos;
    xpos = 0;
  }
  if (ypos < 0) {
    src += -ypos * src_stride;
    src_height -= -ypos;
    ypos = 0;
  }
  /* adjust width/height if the src is bigger than dest */
  if (xpos + src_width > dest_width) {
    src_width = dest_width - xpos;
  }
  if (ypos + src_height > dest_height) {
    src_height = dest_height - ypos;
  }

  src_add = src_stride - (4 * src_width);
  dest_add = dest_stride - (4 * src_width);

  dest = dest + 4 * xpos + (ypos * dest_stride);

  /* we convert a square of 2x2 samples to generate 4 Luma and 2 chroma samples */
  for (i = 0; i < src_height; i++) {
    for (j = 0; j < src_width; j++) {
      alpha = (src[0] * b_alpha) >> 8;
      BLEND_MODE (dest[1], dest[2], dest[3], src[1], src[2], src[3],
          alpha, Y, U, V);
      dest[0] = 0xff;
      dest[1] = Y;
      dest[2] = U;
      dest[3] = V;

      src += 4;
      dest += 4;
    }
    src += src_add;
    dest += dest_add;
  }
}

#undef BLEND_MODE

static int
pad_zorder_compare (const GstVideoMixerPad * pad1,
    const GstVideoMixerPad * pad2)
{
  return pad1->zorder - pad2->zorder;
}

static void
gst_videomixer_sort_pads (GstVideoMixer * mix)
{
  mix->sinkpads = g_slist_sort (mix->sinkpads,
      (GCompareFunc) pad_zorder_compare);
}

/* fill a buffer with a checkerboard pattern */
static void
gst_videomixer_fill_checker (guint8 * dest, gint width, gint height)
{
  gint i, j;
  static int tab[] = { 80, 160, 80, 160 };

  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      *dest++ = 0xff;
      *dest++ = tab[((i & 0x8) >> 3) + ((j & 0x8) >> 3)];
      *dest++ = 128;
      *dest++ = 128;
    }
  }
}

static void
gst_videomixer_fill_color (guint8 * dest, gint width, gint height,
    gint colY, gint colU, gint colV)
{
  gint i, j;

  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      *dest++ = 0xff;
      *dest++ = colY;
      *dest++ = colU;
      *dest++ = colV;
    }
  }
}

/* try to get a buffer on all pads. As long as the queued value is
 * negative, we skip buffers */
static gboolean
gst_videomixer_fill_queues (GstVideoMixer * mix)
{
  GSList *walk = NULL;

  gboolean eos = TRUE;

  g_return_val_if_fail (GST_IS_VIDEO_MIXER (mix), FALSE);

  /* try to make sure we have a buffer from each usable pad first */
  walk = mix->collect->data;
  while (walk) {
    GstCollectData *data = (GstCollectData *) walk->data;

    GstVideoMixerCollect *mixcol = (GstVideoMixerCollect *) data;

    GstVideoMixerPad *mixpad = mixcol->mixpad;

    walk = g_slist_next (walk);

    if (mixcol->buffer == NULL) {
      GstBuffer *buf = NULL;

      GST_LOG ("we need a new buffer");

      buf = gst_collect_pads_pop (mix->collect, data);

      if (buf) {
        guint64 duration;

        GST_LOG ("we have a buffer !");

        mixcol->buffer = buf;
        duration = GST_BUFFER_DURATION (mixcol->buffer);
        /* no duration on the buffer, use the framerate */
        if (!GST_CLOCK_TIME_IS_VALID (duration)) {
          if (mixpad->fps_n == 0) {
            duration = GST_CLOCK_TIME_NONE;
          } else {
            duration = GST_SECOND * mixpad->fps_d / mixpad->fps_n;
          }
        }
        if (GST_CLOCK_TIME_IS_VALID (duration))
          mixpad->queued += duration;
        else if (!mixpad->queued)
          mixpad->queued = GST_CLOCK_TIME_NONE;
      } else {
        GST_LOG ("pop returned a NULL buffer");
      }
    }
    if (mix->sendseg && (mixpad == mix->master)) {
      GstEvent *event;
      gint64 stop, start;

      GstSegment *segment = &data->segment;

      /* FIXME, use rate/applied_rate as set on all sinkpads.
       * - currently we just set rate as received from last seek-event
       * We could potentially figure out the duration as well using
       * the current segment positions and the stated stop positions.
       * Also we just start from stream time 0 which is rather
       * weird. For non-synchronized mixing, the time should be
       * the min of the stream times of all received segments,
       * rationale being that the duration is at least going to
       * be as long as the earliest stream we start mixing. This
       * would also be correct for synchronized mixing but then
       * the later streams would be delayed until the stream times
       * match.
       */
      GST_INFO ("_sending play segment");

      start = segment->accum;

      /* get the duration of the segment if we can and add it to the accumulated
       * time on the segment. */
      if (segment->stop != -1 && segment->start != -1)
        stop = start + (segment->stop - segment->start);
      else
        stop = -1;

      event = gst_event_new_new_segment_full (FALSE, segment->rate, 1.0,
          segment->format, start, stop, start + mix->segment_position);
      gst_pad_push_event (mix->srcpad, event);
      mix->sendseg = FALSE;
    }

    if (mixcol->buffer != NULL && GST_CLOCK_TIME_IS_VALID (mixpad->queued)) {
      /* got a buffer somewhere so we're not eos */
      eos = FALSE;
    }
  }

  return eos;
}

/* blend all buffers present on the pads */
static void
gst_videomixer_blend_buffers (GstVideoMixer * mix, GstBuffer * outbuf)
{
  GSList *walk;

  walk = mix->sinkpads;
  while (walk) {                /* We walk with this list because it's ordered */
    GstVideoMixerPad *pad = GST_VIDEO_MIXER_PAD (walk->data);

    GstVideoMixerCollect *mixcol = pad->mixcol;

    walk = g_slist_next (walk);

    if (mixcol->buffer != NULL) {
      GstClockTime timestamp;
      gint64 stream_time;
      GstSegment *seg;

      seg = &mixcol->collect.segment;

      timestamp = GST_BUFFER_TIMESTAMP (mixcol->buffer);

      stream_time =
          gst_segment_to_stream_time (seg, GST_FORMAT_TIME, timestamp);

      /* sync object properties on stream time */
      if (GST_CLOCK_TIME_IS_VALID (stream_time))
        gst_object_sync_values (G_OBJECT (pad), stream_time);

      gst_videomixer_blend_ayuv_ayuv (GST_BUFFER_DATA (mixcol->buffer),
          pad->xpos, pad->ypos, pad->in_width, pad->in_height, pad->alpha,
          GST_BUFFER_DATA (outbuf), mix->out_width, mix->out_height);

      if (pad == mix->master) {
        gint64 running_time;

        running_time =
            gst_segment_to_running_time (seg, GST_FORMAT_TIME, timestamp);

        /* outgoing buffers need the running_time */
        GST_BUFFER_TIMESTAMP (outbuf) = running_time;
        GST_BUFFER_DURATION (outbuf) = GST_BUFFER_DURATION (mixcol->buffer);

        mix->last_ts = running_time;
        if (GST_BUFFER_DURATION_IS_VALID (outbuf))
          mix->last_ts += GST_BUFFER_DURATION (outbuf);
      }
    }
  }
}

/* remove buffers from the queue that were expired in the
 * interval of the master, we also prepare the queued value
 * in the pad so that we can skip and fill buffers later on */
static void
gst_videomixer_update_queues (GstVideoMixer * mix)
{
  GSList *walk;

  guint64 interval;

  interval = mix->master->queued;
  if (interval <= 0) {
    if (mix->fps_n == 0) {
      interval = G_MAXINT64;
    } else {
      interval = GST_SECOND * mix->fps_d / mix->fps_n;
    }
    GST_DEBUG_OBJECT (mix, "set interval to %" G_GUINT64_FORMAT, interval);
  }

  walk = mix->sinkpads;
  while (walk) {
    GstVideoMixerPad *pad = GST_VIDEO_MIXER_PAD (walk->data);

    GstVideoMixerCollect *mixcol = pad->mixcol;

    walk = g_slist_next (walk);

    if (mixcol->buffer != NULL) {
      pad->queued -= interval;
      GST_DEBUG_OBJECT (pad, "queued now %" G_GINT64_FORMAT, pad->queued);
      if (pad->queued <= 0) {
        GST_DEBUG ("unreffing buffer");
        gst_buffer_unref (mixcol->buffer);
        mixcol->buffer = NULL;
      }
    }
  }
}

static GstFlowReturn
gst_videomixer_collected (GstCollectPads * pads, GstVideoMixer * mix)
{
  GstFlowReturn ret = GST_FLOW_OK;

  GstBuffer *outbuf = NULL;

  size_t outsize = 0;

  gboolean eos = FALSE;

  g_return_val_if_fail (GST_IS_VIDEO_MIXER (mix), GST_FLOW_ERROR);

  GST_LOG ("all pads are collected");
  GST_VIDEO_MIXER_STATE_LOCK (mix);

  eos = gst_videomixer_fill_queues (mix);

  if (eos) {
    /* Push EOS downstream */
    GST_LOG ("all our sinkpads are EOS, pushing downstream");
    gst_pad_push_event (mix->srcpad, gst_event_new_eos ());
    ret = GST_FLOW_WRONG_STATE;
    goto error;
  }

  /* Calculating out buffer size from input size */
  outsize = 4 * mix->in_width * GST_ROUND_UP_2 (mix->in_height);

  /* If geometry has changed we need to set new caps on the buffer */
  if (mix->in_width != mix->out_width || mix->in_height != mix->out_height
      || mix->setcaps) {
    GstCaps *newcaps = NULL;

    newcaps = gst_caps_make_writable
        (gst_pad_get_negotiated_caps (GST_PAD (mix->master)));
    gst_caps_set_simple (newcaps,
        "format", GST_TYPE_FOURCC, GST_STR_FOURCC ("AYUV"),
        "width", G_TYPE_INT, mix->in_width,
        "height", G_TYPE_INT, mix->in_height, NULL);

    mix->out_width = mix->in_width;
    mix->out_height = mix->in_height;
    mix->setcaps = FALSE;

    ret =
        gst_pad_alloc_buffer_and_set_caps (mix->srcpad, GST_BUFFER_OFFSET_NONE,
        outsize, newcaps, &outbuf);
    gst_caps_unref (newcaps);
  } else {                      /* Otherwise we just allocate a buffer from current caps */
    ret =
        gst_pad_alloc_buffer_and_set_caps (mix->srcpad, GST_BUFFER_OFFSET_NONE,
        outsize, GST_PAD_CAPS (mix->srcpad), &outbuf);
  }

  if (ret != GST_FLOW_OK) {
    goto error;
  }

  switch (mix->background) {
    case VIDEO_MIXER_BACKGROUND_CHECKER:
      gst_videomixer_fill_checker (GST_BUFFER_DATA (outbuf),
          mix->out_width, mix->out_height);
      break;
    case VIDEO_MIXER_BACKGROUND_BLACK:
      gst_videomixer_fill_color (GST_BUFFER_DATA (outbuf),
          mix->out_width, mix->out_height, 16, 128, 128);
      break;
    case VIDEO_MIXER_BACKGROUND_WHITE:
      gst_videomixer_fill_color (GST_BUFFER_DATA (outbuf),
          mix->out_width, mix->out_height, 240, 128, 128);
      break;
  }

  gst_videomixer_blend_buffers (mix, outbuf);

  gst_videomixer_update_queues (mix);
  GST_VIDEO_MIXER_STATE_UNLOCK (mix);

  ret = gst_pad_push (mix->srcpad, outbuf);

beach:
  return ret;

  /* ERRORS */
error:
  {
    GST_VIDEO_MIXER_STATE_UNLOCK (mix);
    goto beach;
  }
}

static gboolean
forward_event_func (GstPad * pad, GValue * ret, GstEvent * event)
{
  gst_event_ref (event);
  GST_LOG_OBJECT (pad, "About to send event %s", GST_EVENT_TYPE_NAME (event));
  if (!gst_pad_push_event (pad, event)) {
    g_value_set_boolean (ret, FALSE);
    GST_WARNING_OBJECT (pad, "Sending event  %p (%s) failed.",
        event, GST_EVENT_TYPE_NAME (event));
  } else {
    GST_LOG_OBJECT (pad, "Sent event  %p (%s).",
        event, GST_EVENT_TYPE_NAME (event));
  }
  gst_object_unref (pad);
  return TRUE;
}

/* forwards the event to all sinkpads, takes ownership of the
 * event
 *
 * Returns: TRUE if the event could be forwarded on all
 * sinkpads.
 */
static gboolean
forward_event (GstVideoMixer * mix, GstEvent * event)
{
  gboolean ret;

  GstIterator *it;
  GValue vret = { 0 };

  GST_LOG_OBJECT (mix, "Forwarding event %p (%s)", event,
      GST_EVENT_TYPE_NAME (event));

  ret = TRUE;

  g_value_init (&vret, G_TYPE_BOOLEAN);
  g_value_set_boolean (&vret, TRUE);
  it = gst_element_iterate_sink_pads (GST_ELEMENT_CAST (mix));
  gst_iterator_fold (it, (GstIteratorFoldFunction) forward_event_func, &vret,
      event);
  gst_iterator_free (it);
  gst_event_unref (event);

  ret = g_value_get_boolean (&vret);

  return ret;
}

static gboolean
gst_videomixer_src_event (GstPad * pad, GstEvent * event)
{
  GstVideoMixer *mix;

  gboolean result;

  mix = GST_VIDEO_MIXER (gst_pad_get_parent (pad));

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_QOS:
      /* QoS might be tricky */
      result = FALSE;
      break;
    case GST_EVENT_SEEK:
    {
      GstSeekFlags flags;

      GstSeekType curtype;

      gint64 cur;

      /* parse the seek parameters */
      gst_event_parse_seek (event, NULL, NULL, &flags, &curtype,
          &cur, NULL, NULL);

      /* check if we are flushing */
      if (flags & GST_SEEK_FLAG_FLUSH) {
        /* make sure we accept nothing anymore and return WRONG_STATE */
        gst_collect_pads_set_flushing (mix->collect, TRUE);

        /* flushing seek, start flush downstream, the flush will be done
         * when all pads received a FLUSH_STOP. */
        gst_pad_push_event (mix->srcpad, gst_event_new_flush_start ());
      }

      /* now wait for the collected to be finished and mark a new
       * segment */
      GST_OBJECT_LOCK (mix->collect);
      if (curtype == GST_SEEK_TYPE_SET)
        mix->segment_position = cur;
      else
        mix->segment_position = 0;
      mix->sendseg = TRUE;
      GST_OBJECT_UNLOCK (mix->collect);

      result = forward_event (mix, event);
      break;
    }
    case GST_EVENT_NAVIGATION:
      /* navigation is rather pointless. */
      result = FALSE;
      break;
    default:
      /* just forward the rest for now */
      result = forward_event (mix, event);
      break;
  }
  gst_object_unref (mix);

  return result;
}

static gboolean
gst_videomixer_sink_event (GstPad * pad, GstEvent * event)
{
  GstVideoMixer *videomixer;

  gboolean ret;

  videomixer = GST_VIDEO_MIXER (gst_pad_get_parent (pad));

  GST_DEBUG ("Got %s event on pad %s:%s", GST_EVENT_TYPE_NAME (event),
      GST_DEBUG_PAD_NAME (pad));

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_FLUSH_STOP:
      /* mark a pending new segment. This event is synchronized
       * with the streaming thread so we can safely update the
       * variable without races. It's somewhat weird because we
       * assume the collectpads forwarded the FLUSH_STOP past us
       * and downstream (using our source pad, the bastard!).
       */
      videomixer->sendseg = TRUE;
      break;
    case GST_EVENT_NEWSEGMENT:
      videomixer->sendseg = TRUE;
      break;
    default:
      break;
  }

  /* now GstCollectPads can take care of the rest, e.g. EOS */
  ret = videomixer->collect_event (pad, event);

  gst_object_unref (videomixer);
  return ret;
}


static void
gst_videomixer_get_property (GObject * object,
    guint prop_id, GValue * value, GParamSpec * pspec)
{
  GstVideoMixer *mix = GST_VIDEO_MIXER (object);

  switch (prop_id) {
    case ARG_BACKGROUND:
      g_value_set_enum (value, mix->background);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_videomixer_set_property (GObject * object,
    guint prop_id, const GValue * value, GParamSpec * pspec)
{
  GstVideoMixer *mix = GST_VIDEO_MIXER (object);

  switch (prop_id) {
    case ARG_BACKGROUND:
      mix->background = g_value_get_enum (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static GstStateChangeReturn
gst_videomixer_change_state (GstElement * element, GstStateChange transition)
{
  GstVideoMixer *mix;

  GstStateChangeReturn ret;

  g_return_val_if_fail (GST_IS_VIDEO_MIXER (element), GST_STATE_CHANGE_FAILURE);

  mix = GST_VIDEO_MIXER (element);

  switch (transition) {
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      GST_LOG ("starting collectpads");
      gst_collect_pads_start (mix->collect);
      break;
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      GST_LOG ("stopping collectpads");
      gst_collect_pads_stop (mix->collect);
      break;
    default:
      break;
  }

  ret = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);

  switch (transition) {
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      gst_videomixer_reset (mix);
      break;
    default:
      break;
  }

  return ret;
}

static gboolean
plugin_init (GstPlugin * plugin)
{
  GST_DEBUG_CATEGORY_INIT (gst_videomixer_debug, "videomixer", 0,
      "video mixer");

  return gst_element_register (plugin, "videomixer", GST_RANK_PRIMARY,
      GST_TYPE_VIDEO_MIXER);
}

GST_PLUGIN_DEFINE (GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    "videomixer",
    "Video mixer", plugin_init, VERSION, GST_LICENSE, GST_PACKAGE_NAME,
    GST_PACKAGE_ORIGIN)
