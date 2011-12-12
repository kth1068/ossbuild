
/* autogenerated from E:\Build\OSSBuild\Main\GStreamer\Windows\.\..\Source\gst-plugins-bad\gst\fieldanalysis\gstfieldanalysisorc.orc */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <glib.h>

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
#define inline __inline
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
#ifndef ORC_RESTRICT
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define ORC_RESTRICT restrict
#elif defined(__GNUC__) && __GNUC__ >= 4
#define ORC_RESTRICT __restrict__
#else
#define ORC_RESTRICT
#endif
#endif

#ifndef DISABLE_ORC
#include <orc/orc.h>
#endif
void orc_same_parity_sad_planar_yuv (guint32 * ORC_RESTRICT a1, const orc_uint8 * ORC_RESTRICT s1, const orc_uint8 * ORC_RESTRICT s2, int p2, int n);
void orc_same_parity_ssd_planar_yuv (guint32 * ORC_RESTRICT a1, const orc_uint8 * ORC_RESTRICT s1, const orc_uint8 * ORC_RESTRICT s2, int p2, int n);
void orc_same_parity_3_tap_planar_yuv (guint32 * ORC_RESTRICT a1, const orc_uint8 * ORC_RESTRICT s1, const orc_uint8 * ORC_RESTRICT s2, const orc_uint8 * ORC_RESTRICT s3, const orc_uint8 * ORC_RESTRICT s4, const orc_uint8 * ORC_RESTRICT s5, const orc_uint8 * ORC_RESTRICT s6, int p2, int n);
void orc_opposite_parity_5_tap_planar_yuv (guint32 * ORC_RESTRICT a1, const orc_uint8 * ORC_RESTRICT s1, const orc_uint8 * ORC_RESTRICT s2, const orc_uint8 * ORC_RESTRICT s3, const orc_uint8 * ORC_RESTRICT s4, const orc_uint8 * ORC_RESTRICT s5, int p2, int n);

void gst_fieldanalysis_orc_init (void);


/* begin Orc C target preamble */
#define ORC_CLAMP(x,a,b) ((x)<(a) ? (a) : ((x)>(b) ? (b) : (x)))
#define ORC_ABS(a) ((a)<0 ? -(a) : (a))
#define ORC_MIN(a,b) ((a)<(b) ? (a) : (b))
#define ORC_MAX(a,b) ((a)>(b) ? (a) : (b))
#define ORC_SB_MAX 127
#define ORC_SB_MIN (-1-ORC_SB_MAX)
#define ORC_UB_MAX 255
#define ORC_UB_MIN 0
#define ORC_SW_MAX 32767
#define ORC_SW_MIN (-1-ORC_SW_MAX)
#define ORC_UW_MAX 65535
#define ORC_UW_MIN 0
#define ORC_SL_MAX 2147483647
#define ORC_SL_MIN (-1-ORC_SL_MAX)
#define ORC_UL_MAX 4294967295U
#define ORC_UL_MIN 0
#define ORC_CLAMP_SB(x) ORC_CLAMP(x,ORC_SB_MIN,ORC_SB_MAX)
#define ORC_CLAMP_UB(x) ORC_CLAMP(x,ORC_UB_MIN,ORC_UB_MAX)
#define ORC_CLAMP_SW(x) ORC_CLAMP(x,ORC_SW_MIN,ORC_SW_MAX)
#define ORC_CLAMP_UW(x) ORC_CLAMP(x,ORC_UW_MIN,ORC_UW_MAX)
#define ORC_CLAMP_SL(x) ORC_CLAMP(x,ORC_SL_MIN,ORC_SL_MAX)
#define ORC_CLAMP_UL(x) ORC_CLAMP(x,ORC_UL_MIN,ORC_UL_MAX)
#define ORC_SWAP_W(x) ((((x)&0xff)<<8) | (((x)&0xff00)>>8))
#define ORC_SWAP_L(x) ((((x)&0xff)<<24) | (((x)&0xff00)<<8) | (((x)&0xff0000)>>8) | (((x)&0xff000000)>>24))
#define ORC_SWAP_Q(x) ((((x)&ORC_UINT64_C(0xff))<<56) | (((x)&ORC_UINT64_C(0xff00))<<40) | (((x)&ORC_UINT64_C(0xff0000))<<24) | (((x)&ORC_UINT64_C(0xff000000))<<8) | (((x)&ORC_UINT64_C(0xff00000000))>>8) | (((x)&ORC_UINT64_C(0xff0000000000))>>24) | (((x)&ORC_UINT64_C(0xff000000000000))>>40) | (((x)&ORC_UINT64_C(0xff00000000000000))>>56))
#define ORC_PTR_OFFSET(ptr,offset) ((void *)(((unsigned char *)(ptr)) + (offset)))
#define ORC_DENORMAL(x) ((x) & ((((x)&0x7f800000) == 0) ? 0xff800000 : 0xffffffff))
#define ORC_ISNAN(x) ((((x)&0x7f800000) == 0x7f800000) && (((x)&0x007fffff) != 0))
#define ORC_DENORMAL_DOUBLE(x) ((x) & ((((x)&ORC_UINT64_C(0x7ff0000000000000)) == 0) ? ORC_UINT64_C(0xfff0000000000000) : ORC_UINT64_C(0xffffffffffffffff)))
#define ORC_ISNAN_DOUBLE(x) ((((x)&ORC_UINT64_C(0x7ff0000000000000)) == ORC_UINT64_C(0x7ff0000000000000)) && (((x)&ORC_UINT64_C(0x000fffffffffffff)) != 0))
#ifndef ORC_RESTRICT
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define ORC_RESTRICT restrict
#elif defined(__GNUC__) && __GNUC__ >= 4
#define ORC_RESTRICT __restrict__
#else
#define ORC_RESTRICT
#endif
#endif
/* end Orc C target preamble */



/* orc_same_parity_sad_planar_yuv */
#ifdef DISABLE_ORC
void
orc_same_parity_sad_planar_yuv (guint32 * ORC_RESTRICT a1, const orc_uint8 * ORC_RESTRICT s1, const orc_uint8 * ORC_RESTRICT s2, int p2, int n){
  int i;
  const orc_int8 * ORC_RESTRICT ptr4;
  const orc_int8 * ORC_RESTRICT ptr5;
  orc_union32 var12 =  { 0 };
  orc_int8 var36;
  orc_int8 var37;
  orc_union32 var38;
  orc_union16 var39;
  orc_union16 var40;
  orc_union16 var41;
  orc_union16 var42;
  orc_union32 var43;
  orc_union32 var44;
  orc_union32 var45;

  ptr4 = (orc_int8 *)s1;
  ptr5 = (orc_int8 *)s2;

    /* 7: loadpl */
    var38.i = p2;

  for (i = 0; i < n; i++) {
    /* 0: loadb */
    var36 = ptr4[i];
    /* 1: convubw */
    var39.i = (orc_uint8)var36;
    /* 2: loadb */
    var37 = ptr5[i];
    /* 3: convubw */
    var40.i = (orc_uint8)var37;
    /* 4: subw */
    var41.i = var39.i - var40.i;
    /* 5: absw */
    var42.i = ORC_ABS(var41.i);
    /* 6: convuwl */
    var43.i = (orc_uint16)var42.i;
    /* 8: cmpgtsl */
    var44.i = (var43.i > var38.i) ? (~0) : 0;
    /* 9: andl */
    var45.i = var43.i & var44.i;
    /* 10: accl */
    var12.i = var12.i + var45.i;
  }
  *a1 = var12.i;

}

#else
static void
_backup_orc_same_parity_sad_planar_yuv (OrcExecutor * ORC_RESTRICT ex)
{
  int i;
  int n = ex->n;
  const orc_int8 * ORC_RESTRICT ptr4;
  const orc_int8 * ORC_RESTRICT ptr5;
  orc_union32 var12 =  { 0 };
  orc_int8 var36;
  orc_int8 var37;
  orc_union32 var38;
  orc_union16 var39;
  orc_union16 var40;
  orc_union16 var41;
  orc_union16 var42;
  orc_union32 var43;
  orc_union32 var44;
  orc_union32 var45;

  ptr4 = (orc_int8 *)ex->arrays[4];
  ptr5 = (orc_int8 *)ex->arrays[5];

    /* 7: loadpl */
    var38.i = ex->params[25];

  for (i = 0; i < n; i++) {
    /* 0: loadb */
    var36 = ptr4[i];
    /* 1: convubw */
    var39.i = (orc_uint8)var36;
    /* 2: loadb */
    var37 = ptr5[i];
    /* 3: convubw */
    var40.i = (orc_uint8)var37;
    /* 4: subw */
    var41.i = var39.i - var40.i;
    /* 5: absw */
    var42.i = ORC_ABS(var41.i);
    /* 6: convuwl */
    var43.i = (orc_uint16)var42.i;
    /* 8: cmpgtsl */
    var44.i = (var43.i > var38.i) ? (~0) : 0;
    /* 9: andl */
    var45.i = var43.i & var44.i;
    /* 10: accl */
    var12.i = var12.i + var45.i;
  }
  ex->accumulators[0] = var12.i;

}

static OrcCode *_orc_code_orc_same_parity_sad_planar_yuv;
void
orc_same_parity_sad_planar_yuv (guint32 * ORC_RESTRICT a1, const orc_uint8 * ORC_RESTRICT s1, const orc_uint8 * ORC_RESTRICT s2, int p2, int n)
{
  OrcExecutor _ex, *ex = &_ex;
  OrcCode *c = _orc_code_orc_same_parity_sad_planar_yuv;
  void (*func) (OrcExecutor *);

  ex->arrays[ORC_VAR_A2] = c;
  ex->program = 0;

  ex->n = n;
  ex->arrays[ORC_VAR_S1] = (void *)s1;
  ex->arrays[ORC_VAR_S2] = (void *)s2;
  ex->params[ORC_VAR_P2] = p2;

  func = c->exec;
  func (ex);
  *a1 = orc_executor_get_accumulator (ex, ORC_VAR_A1);
}
#endif


/* orc_same_parity_ssd_planar_yuv */
#ifdef DISABLE_ORC
void
orc_same_parity_ssd_planar_yuv (guint32 * ORC_RESTRICT a1, const orc_uint8 * ORC_RESTRICT s1, const orc_uint8 * ORC_RESTRICT s2, int p2, int n){
  int i;
  const orc_int8 * ORC_RESTRICT ptr4;
  const orc_int8 * ORC_RESTRICT ptr5;
  orc_union32 var12 =  { 0 };
  orc_int8 var36;
  orc_int8 var37;
  orc_union32 var38;
  orc_union16 var39;
  orc_union16 var40;
  orc_union16 var41;
  orc_union32 var42;
  orc_union32 var43;
  orc_union32 var44;

  ptr4 = (orc_int8 *)s1;
  ptr5 = (orc_int8 *)s2;

    /* 6: loadpl */
    var38.i = p2;

  for (i = 0; i < n; i++) {
    /* 0: loadb */
    var36 = ptr4[i];
    /* 1: convubw */
    var39.i = (orc_uint8)var36;
    /* 2: loadb */
    var37 = ptr5[i];
    /* 3: convubw */
    var40.i = (orc_uint8)var37;
    /* 4: subw */
    var41.i = var39.i - var40.i;
    /* 5: mulswl */
    var42.i = var41.i * var41.i;
    /* 7: cmpgtsl */
    var43.i = (var42.i > var38.i) ? (~0) : 0;
    /* 8: andl */
    var44.i = var42.i & var43.i;
    /* 9: accl */
    var12.i = var12.i + var44.i;
  }
  *a1 = var12.i;

}

#else
static void
_backup_orc_same_parity_ssd_planar_yuv (OrcExecutor * ORC_RESTRICT ex)
{
  int i;
  int n = ex->n;
  const orc_int8 * ORC_RESTRICT ptr4;
  const orc_int8 * ORC_RESTRICT ptr5;
  orc_union32 var12 =  { 0 };
  orc_int8 var36;
  orc_int8 var37;
  orc_union32 var38;
  orc_union16 var39;
  orc_union16 var40;
  orc_union16 var41;
  orc_union32 var42;
  orc_union32 var43;
  orc_union32 var44;

  ptr4 = (orc_int8 *)ex->arrays[4];
  ptr5 = (orc_int8 *)ex->arrays[5];

    /* 6: loadpl */
    var38.i = ex->params[25];

  for (i = 0; i < n; i++) {
    /* 0: loadb */
    var36 = ptr4[i];
    /* 1: convubw */
    var39.i = (orc_uint8)var36;
    /* 2: loadb */
    var37 = ptr5[i];
    /* 3: convubw */
    var40.i = (orc_uint8)var37;
    /* 4: subw */
    var41.i = var39.i - var40.i;
    /* 5: mulswl */
    var42.i = var41.i * var41.i;
    /* 7: cmpgtsl */
    var43.i = (var42.i > var38.i) ? (~0) : 0;
    /* 8: andl */
    var44.i = var42.i & var43.i;
    /* 9: accl */
    var12.i = var12.i + var44.i;
  }
  ex->accumulators[0] = var12.i;

}

static OrcCode *_orc_code_orc_same_parity_ssd_planar_yuv;
void
orc_same_parity_ssd_planar_yuv (guint32 * ORC_RESTRICT a1, const orc_uint8 * ORC_RESTRICT s1, const orc_uint8 * ORC_RESTRICT s2, int p2, int n)
{
  OrcExecutor _ex, *ex = &_ex;
  OrcCode *c = _orc_code_orc_same_parity_ssd_planar_yuv;
  void (*func) (OrcExecutor *);

  ex->arrays[ORC_VAR_A2] = c;
  ex->program = 0;

  ex->n = n;
  ex->arrays[ORC_VAR_S1] = (void *)s1;
  ex->arrays[ORC_VAR_S2] = (void *)s2;
  ex->params[ORC_VAR_P2] = p2;

  func = c->exec;
  func (ex);
  *a1 = orc_executor_get_accumulator (ex, ORC_VAR_A1);
}
#endif


/* orc_same_parity_3_tap_planar_yuv */
#ifdef DISABLE_ORC
void
orc_same_parity_3_tap_planar_yuv (guint32 * ORC_RESTRICT a1, const orc_uint8 * ORC_RESTRICT s1, const orc_uint8 * ORC_RESTRICT s2, const orc_uint8 * ORC_RESTRICT s3, const orc_uint8 * ORC_RESTRICT s4, const orc_uint8 * ORC_RESTRICT s5, const orc_uint8 * ORC_RESTRICT s6, int p2, int n){
  int i;
  const orc_int8 * ORC_RESTRICT ptr4;
  const orc_int8 * ORC_RESTRICT ptr5;
  const orc_int8 * ORC_RESTRICT ptr6;
  const orc_int8 * ORC_RESTRICT ptr7;
  const orc_int8 * ORC_RESTRICT ptr8;
  const orc_int8 * ORC_RESTRICT ptr9;
  orc_union32 var12 =  { 0 };
  orc_int8 var40;
  orc_int8 var41;
  orc_int8 var42;
  orc_int8 var43;
  orc_int8 var44;
  orc_int8 var45;
  orc_union32 var46;
  orc_union16 var47;
  orc_union16 var48;
  orc_union16 var49;
  orc_union16 var50;
  orc_union16 var51;
  orc_union16 var52;
  orc_union16 var53;
  orc_union16 var54;
  orc_union16 var55;
  orc_union16 var56;
  orc_union16 var57;
  orc_union16 var58;
  orc_union16 var59;
  orc_union16 var60;
  orc_union32 var61;
  orc_union32 var62;
  orc_union32 var63;

  ptr4 = (orc_int8 *)s1;
  ptr5 = (orc_int8 *)s2;
  ptr6 = (orc_int8 *)s3;
  ptr7 = (orc_int8 *)s4;
  ptr8 = (orc_int8 *)s5;
  ptr9 = (orc_int8 *)s6;

    /* 21: loadpl */
    var46.i = p2;

  for (i = 0; i < n; i++) {
    /* 0: loadb */
    var40 = ptr4[i];
    /* 1: convubw */
    var47.i = (orc_uint8)var40;
    /* 2: loadb */
    var41 = ptr5[i];
    /* 3: convubw */
    var48.i = (orc_uint8)var41;
    /* 4: loadb */
    var42 = ptr6[i];
    /* 5: convubw */
    var49.i = (orc_uint8)var42;
    /* 6: loadb */
    var43 = ptr7[i];
    /* 7: convubw */
    var50.i = (orc_uint8)var43;
    /* 8: loadb */
    var44 = ptr8[i];
    /* 9: convubw */
    var51.i = (orc_uint8)var44;
    /* 10: loadb */
    var45 = ptr9[i];
    /* 11: convubw */
    var52.i = (orc_uint8)var45;
    /* 12: shlw */
    var53.i = var48.i << 2;
    /* 13: shlw */
    var54.i = var51.i << 2;
    /* 14: addw */
    var55.i = var47.i + var53.i;
    /* 15: addw */
    var56.i = var55.i + var49.i;
    /* 16: addw */
    var57.i = var50.i + var54.i;
    /* 17: addw */
    var58.i = var57.i + var52.i;
    /* 18: subw */
    var59.i = var56.i - var58.i;
    /* 19: absw */
    var60.i = ORC_ABS(var59.i);
    /* 20: convuwl */
    var61.i = (orc_uint16)var60.i;
    /* 22: cmpgtsl */
    var62.i = (var61.i > var46.i) ? (~0) : 0;
    /* 23: andl */
    var63.i = var61.i & var62.i;
    /* 24: accl */
    var12.i = var12.i + var63.i;
  }
  *a1 = var12.i;

}

#else
static void
_backup_orc_same_parity_3_tap_planar_yuv (OrcExecutor * ORC_RESTRICT ex)
{
  int i;
  int n = ex->n;
  const orc_int8 * ORC_RESTRICT ptr4;
  const orc_int8 * ORC_RESTRICT ptr5;
  const orc_int8 * ORC_RESTRICT ptr6;
  const orc_int8 * ORC_RESTRICT ptr7;
  const orc_int8 * ORC_RESTRICT ptr8;
  const orc_int8 * ORC_RESTRICT ptr9;
  orc_union32 var12 =  { 0 };
  orc_int8 var40;
  orc_int8 var41;
  orc_int8 var42;
  orc_int8 var43;
  orc_int8 var44;
  orc_int8 var45;
  orc_union32 var46;
  orc_union16 var47;
  orc_union16 var48;
  orc_union16 var49;
  orc_union16 var50;
  orc_union16 var51;
  orc_union16 var52;
  orc_union16 var53;
  orc_union16 var54;
  orc_union16 var55;
  orc_union16 var56;
  orc_union16 var57;
  orc_union16 var58;
  orc_union16 var59;
  orc_union16 var60;
  orc_union32 var61;
  orc_union32 var62;
  orc_union32 var63;

  ptr4 = (orc_int8 *)ex->arrays[4];
  ptr5 = (orc_int8 *)ex->arrays[5];
  ptr6 = (orc_int8 *)ex->arrays[6];
  ptr7 = (orc_int8 *)ex->arrays[7];
  ptr8 = (orc_int8 *)ex->arrays[8];
  ptr9 = (orc_int8 *)ex->arrays[9];

    /* 21: loadpl */
    var46.i = ex->params[25];

  for (i = 0; i < n; i++) {
    /* 0: loadb */
    var40 = ptr4[i];
    /* 1: convubw */
    var47.i = (orc_uint8)var40;
    /* 2: loadb */
    var41 = ptr5[i];
    /* 3: convubw */
    var48.i = (orc_uint8)var41;
    /* 4: loadb */
    var42 = ptr6[i];
    /* 5: convubw */
    var49.i = (orc_uint8)var42;
    /* 6: loadb */
    var43 = ptr7[i];
    /* 7: convubw */
    var50.i = (orc_uint8)var43;
    /* 8: loadb */
    var44 = ptr8[i];
    /* 9: convubw */
    var51.i = (orc_uint8)var44;
    /* 10: loadb */
    var45 = ptr9[i];
    /* 11: convubw */
    var52.i = (orc_uint8)var45;
    /* 12: shlw */
    var53.i = var48.i << 2;
    /* 13: shlw */
    var54.i = var51.i << 2;
    /* 14: addw */
    var55.i = var47.i + var53.i;
    /* 15: addw */
    var56.i = var55.i + var49.i;
    /* 16: addw */
    var57.i = var50.i + var54.i;
    /* 17: addw */
    var58.i = var57.i + var52.i;
    /* 18: subw */
    var59.i = var56.i - var58.i;
    /* 19: absw */
    var60.i = ORC_ABS(var59.i);
    /* 20: convuwl */
    var61.i = (orc_uint16)var60.i;
    /* 22: cmpgtsl */
    var62.i = (var61.i > var46.i) ? (~0) : 0;
    /* 23: andl */
    var63.i = var61.i & var62.i;
    /* 24: accl */
    var12.i = var12.i + var63.i;
  }
  ex->accumulators[0] = var12.i;

}

static OrcCode *_orc_code_orc_same_parity_3_tap_planar_yuv;
void
orc_same_parity_3_tap_planar_yuv (guint32 * ORC_RESTRICT a1, const orc_uint8 * ORC_RESTRICT s1, const orc_uint8 * ORC_RESTRICT s2, const orc_uint8 * ORC_RESTRICT s3, const orc_uint8 * ORC_RESTRICT s4, const orc_uint8 * ORC_RESTRICT s5, const orc_uint8 * ORC_RESTRICT s6, int p2, int n)
{
  OrcExecutor _ex, *ex = &_ex;
  OrcCode *c = _orc_code_orc_same_parity_3_tap_planar_yuv;
  void (*func) (OrcExecutor *);

  ex->arrays[ORC_VAR_A2] = c;
  ex->program = 0;

  ex->n = n;
  ex->arrays[ORC_VAR_S1] = (void *)s1;
  ex->arrays[ORC_VAR_S2] = (void *)s2;
  ex->arrays[ORC_VAR_S3] = (void *)s3;
  ex->arrays[ORC_VAR_S4] = (void *)s4;
  ex->arrays[ORC_VAR_S5] = (void *)s5;
  ex->arrays[ORC_VAR_S6] = (void *)s6;
  ex->params[ORC_VAR_P2] = p2;

  func = c->exec;
  func (ex);
  *a1 = orc_executor_get_accumulator (ex, ORC_VAR_A1);
}
#endif


/* orc_opposite_parity_5_tap_planar_yuv */
#ifdef DISABLE_ORC
void
orc_opposite_parity_5_tap_planar_yuv (guint32 * ORC_RESTRICT a1, const orc_uint8 * ORC_RESTRICT s1, const orc_uint8 * ORC_RESTRICT s2, const orc_uint8 * ORC_RESTRICT s3, const orc_uint8 * ORC_RESTRICT s4, const orc_uint8 * ORC_RESTRICT s5, int p2, int n){
  int i;
  const orc_int8 * ORC_RESTRICT ptr4;
  const orc_int8 * ORC_RESTRICT ptr5;
  const orc_int8 * ORC_RESTRICT ptr6;
  const orc_int8 * ORC_RESTRICT ptr7;
  const orc_int8 * ORC_RESTRICT ptr8;
  orc_union32 var12 =  { 0 };
  orc_int8 var39;
  orc_int8 var40;
  orc_int8 var41;
  orc_int8 var42;
  orc_int8 var43;
  orc_union16 var44;
  orc_union16 var45;
  orc_union32 var46;
  orc_union16 var47;
  orc_union16 var48;
  orc_union16 var49;
  orc_union16 var50;
  orc_union16 var51;
  orc_union16 var52;
  orc_union16 var53;
  orc_union16 var54;
  orc_union16 var55;
  orc_union16 var56;
  orc_union16 var57;
  orc_union16 var58;
  orc_union16 var59;
  orc_union32 var60;
  orc_union32 var61;
  orc_union32 var62;

  ptr4 = (orc_int8 *)s1;
  ptr5 = (orc_int8 *)s2;
  ptr6 = (orc_int8 *)s3;
  ptr7 = (orc_int8 *)s4;
  ptr8 = (orc_int8 *)s5;

    /* 11: loadpw */
    var44.i = (int)0x00000003; /* 3 or 1.4822e-323f */
    /* 13: loadpw */
    var45.i = (int)0x00000003; /* 3 or 1.4822e-323f */
    /* 21: loadpl */
    var46.i = p2;

  for (i = 0; i < n; i++) {
    /* 0: loadb */
    var39 = ptr4[i];
    /* 1: convubw */
    var47.i = (orc_uint8)var39;
    /* 2: loadb */
    var40 = ptr5[i];
    /* 3: convubw */
    var48.i = (orc_uint8)var40;
    /* 4: loadb */
    var41 = ptr6[i];
    /* 5: convubw */
    var49.i = (orc_uint8)var41;
    /* 6: loadb */
    var42 = ptr7[i];
    /* 7: convubw */
    var50.i = (orc_uint8)var42;
    /* 8: loadb */
    var43 = ptr8[i];
    /* 9: convubw */
    var51.i = (orc_uint8)var43;
    /* 10: shlw */
    var52.i = var49.i << 2;
    /* 12: mullw */
    var53.i = (var48.i * var44.i) & 0xffff;
    /* 14: mullw */
    var54.i = (var50.i * var45.i) & 0xffff;
    /* 15: subw */
    var55.i = var47.i - var53.i;
    /* 16: addw */
    var56.i = var55.i + var52.i;
    /* 17: subw */
    var57.i = var56.i - var54.i;
    /* 18: addw */
    var58.i = var57.i + var51.i;
    /* 19: absw */
    var59.i = ORC_ABS(var58.i);
    /* 20: convuwl */
    var60.i = (orc_uint16)var59.i;
    /* 22: cmpgtsl */
    var61.i = (var60.i > var46.i) ? (~0) : 0;
    /* 23: andl */
    var62.i = var60.i & var61.i;
    /* 24: accl */
    var12.i = var12.i + var62.i;
  }
  *a1 = var12.i;

}

#else
static void
_backup_orc_opposite_parity_5_tap_planar_yuv (OrcExecutor * ORC_RESTRICT ex)
{
  int i;
  int n = ex->n;
  const orc_int8 * ORC_RESTRICT ptr4;
  const orc_int8 * ORC_RESTRICT ptr5;
  const orc_int8 * ORC_RESTRICT ptr6;
  const orc_int8 * ORC_RESTRICT ptr7;
  const orc_int8 * ORC_RESTRICT ptr8;
  orc_union32 var12 =  { 0 };
  orc_int8 var39;
  orc_int8 var40;
  orc_int8 var41;
  orc_int8 var42;
  orc_int8 var43;
  orc_union16 var44;
  orc_union16 var45;
  orc_union32 var46;
  orc_union16 var47;
  orc_union16 var48;
  orc_union16 var49;
  orc_union16 var50;
  orc_union16 var51;
  orc_union16 var52;
  orc_union16 var53;
  orc_union16 var54;
  orc_union16 var55;
  orc_union16 var56;
  orc_union16 var57;
  orc_union16 var58;
  orc_union16 var59;
  orc_union32 var60;
  orc_union32 var61;
  orc_union32 var62;

  ptr4 = (orc_int8 *)ex->arrays[4];
  ptr5 = (orc_int8 *)ex->arrays[5];
  ptr6 = (orc_int8 *)ex->arrays[6];
  ptr7 = (orc_int8 *)ex->arrays[7];
  ptr8 = (orc_int8 *)ex->arrays[8];

    /* 11: loadpw */
    var44.i = (int)0x00000003; /* 3 or 1.4822e-323f */
    /* 13: loadpw */
    var45.i = (int)0x00000003; /* 3 or 1.4822e-323f */
    /* 21: loadpl */
    var46.i = ex->params[25];

  for (i = 0; i < n; i++) {
    /* 0: loadb */
    var39 = ptr4[i];
    /* 1: convubw */
    var47.i = (orc_uint8)var39;
    /* 2: loadb */
    var40 = ptr5[i];
    /* 3: convubw */
    var48.i = (orc_uint8)var40;
    /* 4: loadb */
    var41 = ptr6[i];
    /* 5: convubw */
    var49.i = (orc_uint8)var41;
    /* 6: loadb */
    var42 = ptr7[i];
    /* 7: convubw */
    var50.i = (orc_uint8)var42;
    /* 8: loadb */
    var43 = ptr8[i];
    /* 9: convubw */
    var51.i = (orc_uint8)var43;
    /* 10: shlw */
    var52.i = var49.i << 2;
    /* 12: mullw */
    var53.i = (var48.i * var44.i) & 0xffff;
    /* 14: mullw */
    var54.i = (var50.i * var45.i) & 0xffff;
    /* 15: subw */
    var55.i = var47.i - var53.i;
    /* 16: addw */
    var56.i = var55.i + var52.i;
    /* 17: subw */
    var57.i = var56.i - var54.i;
    /* 18: addw */
    var58.i = var57.i + var51.i;
    /* 19: absw */
    var59.i = ORC_ABS(var58.i);
    /* 20: convuwl */
    var60.i = (orc_uint16)var59.i;
    /* 22: cmpgtsl */
    var61.i = (var60.i > var46.i) ? (~0) : 0;
    /* 23: andl */
    var62.i = var60.i & var61.i;
    /* 24: accl */
    var12.i = var12.i + var62.i;
  }
  ex->accumulators[0] = var12.i;

}

static OrcCode *_orc_code_orc_opposite_parity_5_tap_planar_yuv;
void
orc_opposite_parity_5_tap_planar_yuv (guint32 * ORC_RESTRICT a1, const orc_uint8 * ORC_RESTRICT s1, const orc_uint8 * ORC_RESTRICT s2, const orc_uint8 * ORC_RESTRICT s3, const orc_uint8 * ORC_RESTRICT s4, const orc_uint8 * ORC_RESTRICT s5, int p2, int n)
{
  OrcExecutor _ex, *ex = &_ex;
  OrcCode *c = _orc_code_orc_opposite_parity_5_tap_planar_yuv;
  void (*func) (OrcExecutor *);

  ex->arrays[ORC_VAR_A2] = c;
  ex->program = 0;

  ex->n = n;
  ex->arrays[ORC_VAR_S1] = (void *)s1;
  ex->arrays[ORC_VAR_S2] = (void *)s2;
  ex->arrays[ORC_VAR_S3] = (void *)s3;
  ex->arrays[ORC_VAR_S4] = (void *)s4;
  ex->arrays[ORC_VAR_S5] = (void *)s5;
  ex->params[ORC_VAR_P2] = p2;

  func = c->exec;
  func (ex);
  *a1 = orc_executor_get_accumulator (ex, ORC_VAR_A1);
}
#endif


void
gst_fieldanalysis_orc_init (void)
{
#ifndef DISABLE_ORC
  {
    /* orc_same_parity_sad_planar_yuv */
    OrcProgram *p;

      p = orc_program_new ();
      orc_program_set_name (p, "orc_same_parity_sad_planar_yuv");
      orc_program_set_backup_function (p, _backup_orc_same_parity_sad_planar_yuv);
      orc_program_add_source (p, 1, "s1");
      orc_program_add_source (p, 1, "s2");
      orc_program_add_accumulator (p, 4, "a1");
      orc_program_add_parameter (p, 4, "p2");
      orc_program_add_temporary (p, 2, "t1");
      orc_program_add_temporary (p, 2, "t2");
      orc_program_add_temporary (p, 4, "t3");
      orc_program_add_temporary (p, 4, "t4");

      orc_program_append_2 (p, "convubw", 0, ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "convubw", 0, ORC_VAR_T2, ORC_VAR_S2, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "subw", 0, ORC_VAR_T1, ORC_VAR_T1, ORC_VAR_T2, ORC_VAR_D1);
      orc_program_append_2 (p, "absw", 0, ORC_VAR_T1, ORC_VAR_T1, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "convuwl", 0, ORC_VAR_T3, ORC_VAR_T1, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "cmpgtsl", 0, ORC_VAR_T4, ORC_VAR_T3, ORC_VAR_P2, ORC_VAR_D1);
      orc_program_append_2 (p, "andl", 0, ORC_VAR_T3, ORC_VAR_T3, ORC_VAR_T4, ORC_VAR_D1);
      orc_program_append_2 (p, "accl", 0, ORC_VAR_A1, ORC_VAR_T3, ORC_VAR_D1, ORC_VAR_D1);

    orc_program_compile (p);

    _orc_code_orc_same_parity_sad_planar_yuv = orc_program_take_code (p);
    orc_program_free (p);
  }
  {
    /* orc_same_parity_ssd_planar_yuv */
    OrcProgram *p;

      p = orc_program_new ();
      orc_program_set_name (p, "orc_same_parity_ssd_planar_yuv");
      orc_program_set_backup_function (p, _backup_orc_same_parity_ssd_planar_yuv);
      orc_program_add_source (p, 1, "s1");
      orc_program_add_source (p, 1, "s2");
      orc_program_add_accumulator (p, 4, "a1");
      orc_program_add_parameter (p, 4, "p2");
      orc_program_add_temporary (p, 2, "t1");
      orc_program_add_temporary (p, 2, "t2");
      orc_program_add_temporary (p, 4, "t3");
      orc_program_add_temporary (p, 4, "t4");

      orc_program_append_2 (p, "convubw", 0, ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "convubw", 0, ORC_VAR_T2, ORC_VAR_S2, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "subw", 0, ORC_VAR_T1, ORC_VAR_T1, ORC_VAR_T2, ORC_VAR_D1);
      orc_program_append_2 (p, "mulswl", 0, ORC_VAR_T3, ORC_VAR_T1, ORC_VAR_T1, ORC_VAR_D1);
      orc_program_append_2 (p, "cmpgtsl", 0, ORC_VAR_T4, ORC_VAR_T3, ORC_VAR_P2, ORC_VAR_D1);
      orc_program_append_2 (p, "andl", 0, ORC_VAR_T3, ORC_VAR_T3, ORC_VAR_T4, ORC_VAR_D1);
      orc_program_append_2 (p, "accl", 0, ORC_VAR_A1, ORC_VAR_T3, ORC_VAR_D1, ORC_VAR_D1);

    orc_program_compile (p);

    _orc_code_orc_same_parity_ssd_planar_yuv = orc_program_take_code (p);
    orc_program_free (p);
  }
  {
    /* orc_same_parity_3_tap_planar_yuv */
    OrcProgram *p;

      p = orc_program_new ();
      orc_program_set_name (p, "orc_same_parity_3_tap_planar_yuv");
      orc_program_set_backup_function (p, _backup_orc_same_parity_3_tap_planar_yuv);
      orc_program_add_source (p, 1, "s1");
      orc_program_add_source (p, 1, "s2");
      orc_program_add_source (p, 1, "s3");
      orc_program_add_source (p, 1, "s4");
      orc_program_add_source (p, 1, "s5");
      orc_program_add_source (p, 1, "s6");
      orc_program_add_accumulator (p, 4, "a1");
      orc_program_add_constant (p, 4, 0x00000002, "c1");
      orc_program_add_parameter (p, 4, "p2");
      orc_program_add_temporary (p, 2, "t1");
      orc_program_add_temporary (p, 2, "t2");
      orc_program_add_temporary (p, 2, "t3");
      orc_program_add_temporary (p, 2, "t4");
      orc_program_add_temporary (p, 2, "t5");
      orc_program_add_temporary (p, 2, "t6");
      orc_program_add_temporary (p, 4, "t7");
      orc_program_add_temporary (p, 4, "t8");

      orc_program_append_2 (p, "convubw", 0, ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "convubw", 0, ORC_VAR_T2, ORC_VAR_S2, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "convubw", 0, ORC_VAR_T3, ORC_VAR_S3, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "convubw", 0, ORC_VAR_T4, ORC_VAR_S4, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "convubw", 0, ORC_VAR_T5, ORC_VAR_S5, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "convubw", 0, ORC_VAR_T6, ORC_VAR_S6, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "shlw", 0, ORC_VAR_T2, ORC_VAR_T2, ORC_VAR_C1, ORC_VAR_D1);
      orc_program_append_2 (p, "shlw", 0, ORC_VAR_T5, ORC_VAR_T5, ORC_VAR_C1, ORC_VAR_D1);
      orc_program_append_2 (p, "addw", 0, ORC_VAR_T1, ORC_VAR_T1, ORC_VAR_T2, ORC_VAR_D1);
      orc_program_append_2 (p, "addw", 0, ORC_VAR_T1, ORC_VAR_T1, ORC_VAR_T3, ORC_VAR_D1);
      orc_program_append_2 (p, "addw", 0, ORC_VAR_T4, ORC_VAR_T4, ORC_VAR_T5, ORC_VAR_D1);
      orc_program_append_2 (p, "addw", 0, ORC_VAR_T4, ORC_VAR_T4, ORC_VAR_T6, ORC_VAR_D1);
      orc_program_append_2 (p, "subw", 0, ORC_VAR_T1, ORC_VAR_T1, ORC_VAR_T4, ORC_VAR_D1);
      orc_program_append_2 (p, "absw", 0, ORC_VAR_T1, ORC_VAR_T1, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "convuwl", 0, ORC_VAR_T7, ORC_VAR_T1, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "cmpgtsl", 0, ORC_VAR_T8, ORC_VAR_T7, ORC_VAR_P2, ORC_VAR_D1);
      orc_program_append_2 (p, "andl", 0, ORC_VAR_T7, ORC_VAR_T7, ORC_VAR_T8, ORC_VAR_D1);
      orc_program_append_2 (p, "accl", 0, ORC_VAR_A1, ORC_VAR_T7, ORC_VAR_D1, ORC_VAR_D1);

    orc_program_compile (p);

    _orc_code_orc_same_parity_3_tap_planar_yuv = orc_program_take_code (p);
    orc_program_free (p);
  }
  {
    /* orc_opposite_parity_5_tap_planar_yuv */
    OrcProgram *p;

      p = orc_program_new ();
      orc_program_set_name (p, "orc_opposite_parity_5_tap_planar_yuv");
      orc_program_set_backup_function (p, _backup_orc_opposite_parity_5_tap_planar_yuv);
      orc_program_add_source (p, 1, "s1");
      orc_program_add_source (p, 1, "s2");
      orc_program_add_source (p, 1, "s3");
      orc_program_add_source (p, 1, "s4");
      orc_program_add_source (p, 1, "s5");
      orc_program_add_accumulator (p, 4, "a1");
      orc_program_add_constant (p, 4, 0x00000002, "c1");
      orc_program_add_constant (p, 4, 0x00000003, "c2");
      orc_program_add_parameter (p, 4, "p2");
      orc_program_add_temporary (p, 2, "t1");
      orc_program_add_temporary (p, 2, "t2");
      orc_program_add_temporary (p, 2, "t3");
      orc_program_add_temporary (p, 2, "t4");
      orc_program_add_temporary (p, 2, "t5");
      orc_program_add_temporary (p, 4, "t6");
      orc_program_add_temporary (p, 4, "t7");

      orc_program_append_2 (p, "convubw", 0, ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "convubw", 0, ORC_VAR_T2, ORC_VAR_S2, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "convubw", 0, ORC_VAR_T3, ORC_VAR_S3, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "convubw", 0, ORC_VAR_T4, ORC_VAR_S4, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "convubw", 0, ORC_VAR_T5, ORC_VAR_S5, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "shlw", 0, ORC_VAR_T3, ORC_VAR_T3, ORC_VAR_C1, ORC_VAR_D1);
      orc_program_append_2 (p, "mullw", 0, ORC_VAR_T2, ORC_VAR_T2, ORC_VAR_C2, ORC_VAR_D1);
      orc_program_append_2 (p, "mullw", 0, ORC_VAR_T4, ORC_VAR_T4, ORC_VAR_C2, ORC_VAR_D1);
      orc_program_append_2 (p, "subw", 0, ORC_VAR_T1, ORC_VAR_T1, ORC_VAR_T2, ORC_VAR_D1);
      orc_program_append_2 (p, "addw", 0, ORC_VAR_T1, ORC_VAR_T1, ORC_VAR_T3, ORC_VAR_D1);
      orc_program_append_2 (p, "subw", 0, ORC_VAR_T1, ORC_VAR_T1, ORC_VAR_T4, ORC_VAR_D1);
      orc_program_append_2 (p, "addw", 0, ORC_VAR_T1, ORC_VAR_T1, ORC_VAR_T5, ORC_VAR_D1);
      orc_program_append_2 (p, "absw", 0, ORC_VAR_T1, ORC_VAR_T1, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "convuwl", 0, ORC_VAR_T6, ORC_VAR_T1, ORC_VAR_D1, ORC_VAR_D1);
      orc_program_append_2 (p, "cmpgtsl", 0, ORC_VAR_T7, ORC_VAR_T6, ORC_VAR_P2, ORC_VAR_D1);
      orc_program_append_2 (p, "andl", 0, ORC_VAR_T6, ORC_VAR_T6, ORC_VAR_T7, ORC_VAR_D1);
      orc_program_append_2 (p, "accl", 0, ORC_VAR_A1, ORC_VAR_T6, ORC_VAR_D1, ORC_VAR_D1);

    orc_program_compile (p);

    _orc_code_orc_opposite_parity_5_tap_planar_yuv = orc_program_take_code (p);
    orc_program_free (p);
  }
#endif
}


