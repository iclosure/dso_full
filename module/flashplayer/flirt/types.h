/*
 Flirt, an SWF rendering library
 Copyright (c) 2004-2006 Dave Hayden <dave@opaque.net>
 All rights reserved.
 
 http://www.opaque.net/flirt/

 This code is distributed under the two-clause BSD license.
 Read the LICENSE file or visit the URL above for details
*/

#ifndef DD_TYPES_H_INCLUDED
#define DD_TYPES_H_INCLUDED

#include "dd.h"
#include <math.h>


#ifdef DD_PLATFORM_SYMBIAN
#include <e32math.h>
#include <e32def.h>
#include <e32std.h>
#endif 

#if defined(WIN32)
// Visual Studio C 6++ ->
#pragma warning( disable : 4244 )  // Disable warning messages in simulation
#pragma warning( disable : 4761 )  // Disable warning "integral size mismatch in argument; conversion supplied"
#pragma warning( disable : 4305)   // truncation from 'const double ' to 'float '
#pragma warning( disable : 4049)   // compiler limit : terminating line number emission
// Visual Studio 2008 ->
#pragma warning( disable : 4996)   // 'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
#endif 

typedef int   fixed ;
typedef int   boolean ; 
typedef signed char SInt8;
typedef unsigned char UInt8;
typedef short SInt16;
typedef unsigned short UInt16;
typedef unsigned long UInt32;


#define _DENORM		(-2)	/* C9X only */
#define _FINITE		(-1)
#define _INFCODE	1
#define _NANCODE	2

		/* return values for testing functions */
#define FINITE	_FINITE
#define INF		_INFCODE
#define NAN		_NANCODE

#ifndef DD_PLATFORM_SYMBIAN
typedef long long SInt64 ; 
#endif

#define FIXED_SHIFT 10

#define FIXED_I(i) ((i)<<FIXED_SHIFT)

/* doesn't work for d<1:
	#define FIXED_D(d) (((int)floor(d))<<FIXED_SHIFT) */

#define FIXED_D(d) ((int)floor((d)*(1<<FIXED_SHIFT)+0.5))

/* fixed from twips */
#define FIXED_T(t) (((t)<<FIXED_SHIFT)/20)

/* shouldn't ever need this, inside dd all units are fixed screen coords
   and twips are never exposed to the user */

#define TWIPS_F(f) (((f)*20)>>FIXED_SHIFT)
#define TWIPS_I(i) ((i)*20)

#define DOUBLE_F(f) (((f)<0)?(-(-(f)/(double)(1<<FIXED_SHIFT))):((f)/(double)(1<<FIXED_SHIFT)))
#define FLOAT_F(f) (((f)<0)?(-(-(f)/(float)(1<<FIXED_SHIFT))):((f)/(float)(1<<FIXED_SHIFT)))
#define INT_F(f) ((f)>>FIXED_SHIFT)

/* the fractional part of f, left scaled up as an int */
#define FRACT_F(f) ((f)&((1<<FIXED_SHIFT)-1))

/* XXX - should be optimized: */
static  fixed
fixed_mult(fixed a, fixed b)
{
	return (fixed)(((long long)a * b) >> FIXED_SHIFT);
}

static  fixed
fixed_divide(fixed a, fixed b)
{
	return FIXED_D(FLOAT_F(a) / FLOAT_F(b));
}

fixed
fixed_sqrt(unsigned int d);

typedef unsigned int ddColor;

#ifdef DD_COLOR_SAMPLE_ARGB
  #define COLOR_ALPHA(c) (((c)>>24)&0xff)
  #define COLOR_RED(c) (((c)>>16)&0xff)
  #define COLOR_GREEN(c) (((c)>>8)&0xff)
  #define COLOR_BLUE(c) ((c)&0xff)
  #define DDCOLOR(a,r,g,b) ((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff))
  #define SETALPHA(c,a) (((c)&0xffffff)|((a)<<24))
#else
  #define COLOR_RED(c) (((c)>>24)&0xff)
  #define COLOR_GREEN(c) (((c)>>16)&0xff)
  #define COLOR_BLUE(c) (((c)>>8)&0xff)
  #define COLOR_ALPHA(c) ((c)&0xff)
  #define DDCOLOR(a,r,g,b) ((((r)&0xff)<<24)|(((g)&0xff)<<16)|(((b)&0xff)<<8)|((a)&0xff))
  #define SETALPHA(c,a) (((c)&0xffffff00)|(a))
#endif

static  ddColor
ddColor_scale(ddColor color, int scale) /* 0x100 = 1.0 */
{
	if ( scale == 0xff )
		return color;

	return ((((color&0xff000000)>>8)*scale) & 0xff000000) |
		(((((color&0x00ff0000)*scale) & 0xff000000) |
	(((color&0x0000ff00)*scale) & 0x00ff0000) |
	(((color&0x000000ff)*scale) & 0x0000ff00)) >> 8);
}

static  ddColor
ddColor_premultiply(ddColor color)
{
	int alpha = COLOR_ALPHA(color);
	
	if ( alpha == 0xff )
		return color;

	return ddColor_scale(SETALPHA(color, 0xff), alpha);
}

#ifndef dd_min
  #define dd_min(a,b) (((a)<(b))?(a):(b))
#endif

#ifndef dd_max
  #define dd_max(a,b) (((a)>(b))?(a):(b))
#endif

#ifndef DD_FALSE
  #define DD_FALSE (boolean)0
#endif

#ifndef DD_TRUE
  #define DD_TRUE (boolean)1
#endif

#ifndef M_PI
#define M_PI 3.14159265358979
#endif

#ifndef M_SQRT2
#define M_SQRT2 1.41421356237309504880
#endif

#ifndef M_SQRT1_2
#define M_SQRT1_2	0.70710678118654752440
#endif

#ifndef M_E
#define M_E		2.7182818284590452354
#endif

#ifndef M_LOG2E
#define M_LOG2E		1.4426950408889634074
#endif

#ifndef M_LOG10E
#define M_LOG10E	0.43429448190325182765
#endif

#ifndef M_LN2
#define M_LN2		0.69314718055994530942
#endif

#ifndef M_LN10
#define M_LN10		2.30258509299404568402
#endif


/* user add */
double rint(double x);
int isnan(double d);
int _isinf(double d);
int finite( double x );
int strcasecmp(const char *s1,const char *s2);
fixed fixed_sqrt(unsigned int x);
///////


#endif /* DD_TYPES_H_INCLUDED */
