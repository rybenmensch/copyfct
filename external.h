#ifndef external_h
#define external_h

#include "ext.h"
#include "ext_buffer.h"
#include "ext_common.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include <bit>

typedef struct _copyfct t_copyfct;

/*
 Copyright (c) 2004 krzYszcz and others.
 Adapted from the pd-cyclone-project by Manolo Müller.
 https://github.com/porres/pd-cyclone
 Source: curve.c
*/

//definitions for curve-coefs
#define CURVE_C1   1e-20
#define CURVE_C2   1.2
#define CURVE_C3   0.41
#define CURVE_C4   0.91

#define PDCYCURVEINITVAL 0.
#define PDCYCURVEPARAM 0.
#define CURVE_MAXSIZE   256

typedef struct _curveseg{
    float   s_target;
    float   s_delta;
    int     s_nhops;
    float   s_ccinput;
    double  s_bb;
    double  s_mm;
}t_curveseg;

void curve_perform(t_copyfct *x);
static void curve_factor(t_copyfct *x, t_float f);
static void curve_coefs(int nhops, double crv, double *bbp, double *mmp);
static void curve_cc(t_copyfct *x, t_curveseg *segp, float f);
static void curve_tick(t_copyfct *x);
static void curve_float(t_copyfct *x, t_float f);

/*
 The following code is from the pure-data project (copyrighted by Miller Puckette and others).
 https://github.com/pure-data/pure-data
 
 The following license applies:
 https://github.com/pure-data/pure-data/blob/master/LICENSE.txt
 */

typedef union{
    t_float f;
    unsigned int ui;
}t_bigorsmall32;

//undefined behavior in c++
static inline int PD_BIGORSMALL(t_float f){
    t_bigorsmall32 pun;
    pun.f = f;
    return((pun.ui & 0x20000000) == ((pun.ui >> 1) & 0x20000000));
}

static inline int CPP_BIGORSMALL(t_float f){
	unsigned int pun = std::bit_cast<unsigned int>(f);
    return((pun & 0x20000000) == ((pun >> 1) & 0x20000000));
}

#endif /* external_h */
