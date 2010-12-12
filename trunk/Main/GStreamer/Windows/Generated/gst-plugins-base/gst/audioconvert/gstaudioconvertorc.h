
/* autogenerated from C:\ossbuild\Main\GStreamer\Windows\.\..\Source\gst-plugins-base\gst\audioconvert\gstaudioconvertorc.orc */

#ifndef _C__OSSBUILD_MAIN_GSTREAMER_WINDOWS______WINDOWS_GENERATED_GST_PLUGINS_BASE_GST_AUDIOCONVERT_GSTAUDIOCONVERTORC_H_
#define _C__OSSBUILD_MAIN_GSTREAMER_WINDOWS______WINDOWS_GENERATED_GST_PLUGINS_BASE_GST_AUDIOCONVERT_GSTAUDIOCONVERTORC_H_

#include <glib.h>

#ifdef __cplusplus
extern "C" {
#endif

void gst_audio_convert_orc_init (void);



#ifndef _ORC_INTEGER_TYPEDEFS_
#define _ORC_INTEGER_TYPEDEFS_
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <stdint.h>
typedef int8_t orc_int8;
typedef int16_t orc_int16;
typedef int32_t orc_int32;
typedef int64_t orc_int64;
typedef uint8_t orc_uint8;
typedef uint16_t orc_uint16;
typedef uint32_t orc_uint32;
typedef uint64_t orc_uint64;
#define ORC_UINT64_C(x) UINT64_C(x)
#elif defined(_MSC_VER)
typedef signed __int8 orc_int8;
typedef signed __int16 orc_int16;
typedef signed __int32 orc_int32;
typedef signed __int64 orc_int64;
typedef unsigned __int8 orc_uint8;
typedef unsigned __int16 orc_uint16;
typedef unsigned __int32 orc_uint32;
typedef unsigned __int64 orc_uint64;
#define ORC_UINT64_C(x) (x##Ui64)
#else
#include <limits.h>
typedef signed char orc_int8;
typedef short orc_int16;
typedef int orc_int32;
typedef unsigned char orc_uint8;
typedef unsigned short orc_uint16;
typedef unsigned int orc_uint32;
#if INT_MAX == LONG_MAX
typedef long long orc_int64;
typedef unsigned long long orc_uint64;
#define ORC_UINT64_C(x) (x##ULL)
#else
typedef long orc_int64;
typedef unsigned long orc_uint64;
#define ORC_UINT64_C(x) (x##UL)
#endif
#endif
typedef union { orc_int16 i; orc_int8 x2[2]; } orc_union16;
typedef union { orc_int32 i; float f; orc_int16 x2[2]; orc_int8 x4[4]; } orc_union32;
typedef union { orc_int64 i; double f; orc_int32 x2[2]; float x2f[2]; orc_int16 x4[4]; } orc_union64;
#endif
void orc_audio_convert_unpack_u8 (gint32 * d1, const guint8 * s1, int p1, int n);
void orc_audio_convert_unpack_s8 (gint32 * d1, const guint8 * s1, int p1, int n);
void orc_audio_convert_unpack_u16 (gint32 * d1, const guint8 * s1, int p1, int n);
void orc_audio_convert_unpack_s16 (gint32 * d1, const guint8 * s1, int p1, int n);
void orc_audio_convert_unpack_u16_swap (gint32 * d1, const guint8 * s1, int p1, int n);
void orc_audio_convert_unpack_s16_swap (gint32 * d1, const guint8 * s1, int p1, int n);
void orc_audio_convert_unpack_u32 (gint32 * d1, const guint8 * s1, int p1, int n);
void orc_audio_convert_unpack_s32 (gint32 * d1, const guint8 * s1, int p1, int n);
void orc_audio_convert_unpack_u32_swap (gint32 * d1, const guint8 * s1, int p1, int n);
void orc_audio_convert_unpack_s32_swap (gint32 * d1, const guint8 * s1, int p1, int n);
void orc_audio_convert_unpack_float_s32 (guint32 * d1, const gfloat * s1, int n);
void orc_audio_convert_unpack_float_s32_swap (guint32 * d1, const gfloat * s1, int n);
void orc_audio_convert_unpack_double_s32 (guint32 * d1, const gdouble * s1, int n);
void orc_audio_convert_unpack_double_s32_swap (guint32 * d1, const gdouble * s1, int n);
void orc_audio_convert_unpack_float_double (gdouble * d1, const gfloat * s1, int n);
void orc_audio_convert_unpack_float_double_swap (gdouble * d1, const gfloat * s1, int n);
void orc_audio_convert_unpack_double_double (gdouble * d1, const gdouble * s1, int n);
void orc_audio_convert_unpack_double_double_swap (gdouble * d1, const gdouble * s1, int n);
void orc_audio_convert_unpack_u8_double (gdouble * d1, const guint8 * s1, int p1, int n);
void orc_audio_convert_unpack_s8_double (gdouble * d1, const guint8 * s1, int p1, int n);
void orc_audio_convert_unpack_u16_double (gdouble * d1, const guint8 * s1, int p1, int n);
void orc_audio_convert_unpack_s16_double (gdouble * d1, const guint8 * s1, int p1, int n);
void orc_audio_convert_unpack_u16_double_swap (gdouble * d1, const guint8 * s1, int p1, int n);
void orc_audio_convert_unpack_s16_double_swap (gdouble * d1, const guint8 * s1, int p1, int n);
void orc_audio_convert_unpack_u32_double (gdouble * d1, const guint8 * s1, int p1, int n);
void orc_audio_convert_unpack_s32_double (gdouble * d1, const guint8 * s1, int p1, int n);
void orc_audio_convert_unpack_u32_double_swap (gdouble * d1, const guint8 * s1, int p1, int n);
void orc_audio_convert_unpack_s32_double_swap (gdouble * d1, const guint8 * s1, int p1, int n);
void orc_audio_convert_pack_u8 (guint8 * d1, const gint32 * s1, int p1, int n);
void orc_audio_convert_pack_s8 (guint8 * d1, const gint32 * s1, int p1, int n);
void orc_audio_convert_pack_u16 (guint8 * d1, const gint32 * s1, int p1, int n);
void orc_audio_convert_pack_s16 (guint8 * d1, const gint32 * s1, int p1, int n);
void orc_audio_convert_pack_u16_swap (guint8 * d1, const gint32 * s1, int p1, int n);
void orc_audio_convert_pack_s16_swap (guint8 * d1, const gint32 * s1, int p1, int n);
void orc_audio_convert_pack_u32 (guint8 * d1, const gint32 * s1, int p1, int n);
void orc_audio_convert_pack_s32 (guint8 * d1, const gint32 * s1, int p1, int n);
void orc_audio_convert_pack_u32_swap (guint8 * d1, const gint32 * s1, int p1, int n);
void orc_audio_convert_pack_s32_swap (guint8 * d1, const gint32 * s1, int p1, int n);
void orc_audio_convert_pack_s32_float (gfloat * d1, const gint32 * s1, int n);
void orc_audio_convert_pack_s32_float_swap (gfloat * d1, const gint32 * s1, int n);
void orc_audio_convert_pack_s32_double (gdouble * d1, const gint32 * s1, int n);
void orc_audio_convert_pack_s32_double_swap (gdouble * d1, const gint32 * s1, int n);
void orc_audio_convert_pack_double_float (gfloat * d1, const gdouble * s1, int n);
void orc_audio_convert_pack_double_float_swap (gfloat * d1, const gdouble * s1, int n);
void orc_audio_convert_pack_double_u8 (guint8 * d1, const gdouble * s1, int p1, int n);
void orc_audio_convert_pack_double_s8 (guint8 * d1, const gdouble * s1, int p1, int n);
void orc_audio_convert_pack_double_u16 (guint8 * d1, const gdouble * s1, int p1, int n);
void orc_audio_convert_pack_double_s16 (guint8 * d1, const gdouble * s1, int p1, int n);
void orc_audio_convert_pack_double_u16_swap (guint8 * d1, const gdouble * s1, int p1, int n);
void orc_audio_convert_pack_double_s16_swap (guint8 * d1, const gdouble * s1, int p1, int n);
void orc_audio_convert_pack_double_u32 (guint8 * d1, const gdouble * s1, int p1, int n);
void orc_audio_convert_pack_double_s32 (guint8 * d1, const gdouble * s1, int p1, int n);
void orc_audio_convert_pack_double_u32_swap (guint8 * d1, const gdouble * s1, int p1, int n);
void orc_audio_convert_pack_double_s32_swap (guint8 * d1, const gdouble * s1, int p1, int n);

#ifdef __cplusplus
}
#endif

#endif

