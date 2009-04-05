/* GStreamer
 * Copyright (C) 2008 Pioneers of the Inevitable <songbird@songbirdnest.com>
 *
 * Authors: Michael Smith <msmith@songbirdnest.com>
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
    
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif  /* 
    
#include <windows.h>
#include <mmreg.h>
#include <msacm.h>
    
#include <gst/gst.h>
#include <gst/riff/riff-media.h>
    
#define ACM_BUFFER_SIZE (64 * 1024)
    
#define GST_TYPE_ACM_MP3_DEC \
    (acmmp3dec_get_type ()) 
#define GST_ACM_MP3_DEC(obj) \
    (G_TYPE_CHECK_INSTANCE_CAST ((obj), GST_TYPE_ACM_MP3_DEC, ACMMP3Dec)) 
#define GST_CAT_DEFAULT acmmp3dec_debug
    GST_DEBUG_CATEGORY_STATIC (acmmp3dec_debug);

    
    
    

    
    
        "width = (int)16, " 
        ", " 
        "rate = (int)[1, MAX]") 

    
    
        "layer = (int)3, " 
        "rate = (int){ 8000, 11025, 12000, 16000, 22050, 24000, " 
        "               32000, 44100, 48000 }, " 
        "parsed = (boolean) true") 

{
  


{
  
  
  
  
  
  
  
  
  
  
      /* Offset into input buffer to write next data */ 
  int offset;
   
      /* Number of bytes written */ 
  int bytes_output;
   
      /* From received caps */ 
  int rate;
   
   
      /* Set in properties */ 
  int selected_bitrate;
   
 


acmmp3dec_caps_from_format (WAVEFORMATEX * fmt) 
{
  
      (gst_riff_strf_auds *) fmt, NULL, NULL, NULL);



{
  
  
  
  
  
  
  
  
  
  dec->infmt.nBlockSize = 0;    // Damn, need to figure this out... Does this
  // even make sense for vbr files? Various random
  // things suggest 417 for no apparent reason?
  // That's the right value for an unpadded
  // 128 kbps 44.1kHz stream I think. Let's try
  // zero to see if it works though. Or one?
  dec->infmt.nFramesPerBlock = 1;
  
                                   value to put here! Encoder-specific and not
                                   stored in the bitstream. */
  



    WAVEFORMATEX * outfmt) 
{
  
  
  
  
  
  
  
  


acmmp3dec_setup (ACMMP3Dec * dec) 
{
  
  

      
  
    
    
  
  
  
  
      acmStreamOpen (&dec->stream, dec->driver, &dec->infmt, dec->outfmt, 
      0, ACM_STREAMOPENF_NONREALTIME);
  
    
    
  
  
  
  
  
  
  
  
  
      /* Ask what buffer size we need to use for our output */ 
      acmStreamSize (dec->stream, ACM_BUFFER_SIZE, 
      ACM_STREAMSIZEF_SOURCE);
  
  
  
  
  
  
    
    
  
  
  
    
  
  
  


acmmp3dec_teardown (ACMMP3Dec * dec) 
{
  
    
    
  
  
    
    
  
  
    
  
    
  
  
    
    
  
  
    
    
  
  
  
  


acmmp3dec_sink_setcaps (GstPad * pad, GstCaps * caps) 
{
  
  
  
  
  
  
  
  
    
  
  


acmmp3dec_push_output (ACMMP3Dec * dec) 
{
  
  
    
        gst_buffer_new_and_alloc (dec->header.cbDstLengthUsed);
    
        
    
    
        gst_util_uint64_scale_int (
        dec->bytes_per_sample);
    
    
        
    
  
  


acmmp3dec_chain (GstPad * pad, GstBuffer * buf) 
{
  
  
  
  
  
  
  
    
    
  
  
    
  
  
  
  
      /* Now we have a buffer ready to go */ 
      res =
      acmStreamConvert (dec->stream, &dec->header,
      
  
    
    
  
  
    
    
      
      
          /* We could handle this, but it shouldn't be possible, so don't try
           * for now */ 
          return GST_FLOW_ERROR;
    
    
        /* Write out any data produced */ 
        acmmp3dec_push_output (dec);
    
  



{
  
  
  
  
  
      /* Flush out any remaining data internal to the decoder */ 
      res =
      acmStreamConvert (dec->stream, &dec->header,
      
  
    
    
  
  
  


acmmp3dec_sink_event (GstPad * pad, GstEvent * event) 
{
  
  
  
    
      
      
      
    
      
    
      
      
  
  


acmmp3dec_dispose (GObject * obj) 
{
  
  


acmmp3dec_init (ACMMP3Dec * dec) 
{
  
      gst_pad_new_from_static_template (&acmmp3dec_sink_template, "sink");
  
      
  
      
  
      
  
  
      gst_pad_new_from_static_template (&acmmp3dec_src_template, "src");
  


acmmp3dec_class_init (ACMMP3DecClass * klass) 
{
  
  


acmmp3dec_base_init (ACMMP3DecClass * klass) 
{
  
  
      
  
      
  


plugin_init (GstPlugin * plugin) 
{
  
  
  
          
    
  
  



    
    GST_PACKAGE_ORIGIN_ '

