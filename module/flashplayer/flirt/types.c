/*
 Flirt, an SWF rendering library
 Copyright (c) 2004-2006 Dave Hayden <dave@opaque.net>
 All rights reserved.
 
 http://www.opaque.net/flirt/

 This code is distributed under the two-clause BSD license.
 Read the LICENSE file or visit the URL above for details
*/

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
//#include <float.h>
//#include <ieee.h>
#include "types.h"

//下面是两个要用到的函数
#ifdef VAX      /* VAX D format */
    static unsigned short msign=0x7fff;
#else           /*IEEE double format */
    static unsigned short msign=0x7fff;
#endif

static
double copysign(x,y)
double x,y;
{
#ifdef NATIONAL
        unsigned short  *px=(unsigned short *) &x+3,
                        *py=(unsigned short *) &y+3;
#else /* VAX, SUN, ZILOG */
        unsigned short  *px=(unsigned short *) &x,
                        *py=(unsigned short *) &y;
#endif

#ifdef VAX
        if ( (*px & mexp) == 0 ) return(x);
#endif

        *px = ( *px & msign ) | ( *py & ~msign );
        return(x);
}

/*
 * algorithm for rint(x) in pseudo-pascal form ...
 *
 * real rint(x): real x;
 *      ... delivers integer nearest x in direction of prevailing rounding
 *      ... mode
 * const        L = (last consecutive integer)/2
 *        = 2**55; for VAX D
 *        = 2**52; for IEEE 754 Double
 * real s,t;
 * begin
 *      if x != x then return x;                ... NaN
 *      if |x| >= L then return x;              ... already an integer
 *      s := copysign(L,x);
 *      t := x + s;                             ... = (x+s) rounded to integer
 *      return t - s
 * end;
 *
 * Note: Inexact will be signaled if x is not an integer, as is
 *      customary for IEEE 754.  No other signal can be emitted.
 */
#ifdef VAX
static long Lx[] = {0x5c00,0x0};                /* 2**55 */
#define L *(double *) Lx
#else   /* IEEE double */
static double L = 4503599627370496.0E0;         /* 2**52 */
#endif
double
rint(x)
double x;
{
        double s,t,one = 1.0,copysign();
#ifndef VAX
        if (x != x)                             /* NaN */
                return (x);
#endif
        if (copysign(x,one) >= L)               /* already an integer */
            return (x);
        s = copysign(L,x);
        t = x + s;                              /* x+s rounded to integer */
        return (t - s);
}

int isnan(double d)

{

   union 

   {

      unsigned long long l;

      double d;

   } u;

   u.d=d;

   return (u.l==0x7FF8000000000000ll || u.l==0x7FF0000000000000ll || u.l==0xfff8000000000000ll);

}

int _isinf(double d) 

{

   union 

   {

      unsigned long long l;

      double d;

   } u;

   u.d=d;

   return (u.l==0x7FF0000000000000ll?1:u.l==0xFFF0000000000000ll?-1:0);

}



int finite( double x )
{
	return !_isinf(x);
}

int
strcasecmp(const char *s1,const char *s2)
{
  while (*s1 != '\0' && tolower(*s1) == tolower(*s2))
    {
      s1++;
      s2++;
    }

  return tolower(*(unsigned char *) s1) - tolower(*(unsigned char *) s2);
}

/*
void dd_free(void *p)
{
  free(p);
}
*/

/* XXX - put this somewhere else */
/*
void error(char* s, ...)
{
  va_list ap;
  va_start(ap, s);
  vprintf(s, ap);
  va_end(ap);
  putchar('\n');
  exit(1);
}
*/

/* (from http://www.azillionmonkeys.com/qed/sqroot.html)
 // Integer Square Root function
 // Contributors include Arne Steinarson for the basic approximation idea, Dann
 // Corbit and Mathew Hendry for the first cut at the algorithm, Lawrence Kirby
 // for the rearrangement, improvments and range optimization and Paul Hsieh
 // for the round-then-adjust idea.
 */
fixed
fixed_sqrt(unsigned int x)
{
    static const unsigned char sqq_table[] = {
		0,  16,  22,  27,  32,  35,  39,  42,  45,  48,  50,  53,  55,  57,
		59,  61,  64,  65,  67,  69,  71,  73,  75,  76,  78,  80,  81,  83,
		84,  86,  87,  89,  90,  91,  93,  94,  96,  97,  98,  99, 101, 102,
		103, 104, 106, 107, 108, 109, 110, 112, 113, 114, 115, 116, 117, 118,
		119, 120, 121, 122, 123, 124, 125, 126, 128, 128, 129, 130, 131, 132,
		133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 144, 145,
		146, 147, 148, 149, 150, 150, 151, 152, 153, 154, 155, 155, 156, 157,
		158, 159, 160, 160, 161, 162, 163, 163, 164, 165, 166, 167, 167, 168,
		169, 170, 170, 171, 172, 173, 173, 174, 175, 176, 176, 177, 178, 178,
		179, 180, 181, 181, 182, 183, 183, 184, 185, 185, 186, 187, 187, 188,
		189, 189, 190, 191, 192, 192, 193, 193, 194, 195, 195, 196, 197, 197,
		198, 199, 199, 200, 201, 201, 202, 203, 203, 204, 204, 205, 206, 206,
		207, 208, 208, 209, 209, 210, 211, 211, 212, 212, 213, 214, 214, 215,
		215, 216, 217, 217, 218, 218, 219, 219, 220, 221, 221, 222, 222, 223,
		224, 224, 225, 225, 226, 226, 227, 227, 228, 229, 229, 230, 230, 231,
		231, 232, 232, 233, 234, 234, 235, 235, 236, 236, 237, 237, 238, 238,
		239, 240, 240, 241, 241, 242, 242, 243, 243, 244, 244, 245, 245, 246,
		246, 247, 247, 248, 248, 249, 249, 250, 250, 251, 251, 252, 252, 253,
		253, 254, 254, 255
    };

	unsigned long xn;

	if (x >= 0x10000)
	{
		if (x >= 0x1000000)
		{
			if (x >= 0x10000000)
			{
				if (x >= 0x40000000)
				{
					if (x >= 65535UL*65535UL)
						return 65535 << (FIXED_SHIFT / 2);
					
					xn = sqq_table[x>>24] << 8;
				}
				else
					xn = sqq_table[x>>22] << 7;
			}
			else
			{
				if (x >= 0x4000000)
					xn = sqq_table[x>>20] << 6;
				else
					xn = sqq_table[x>>18] << 5;
			}
		}
		else
		{
			if (x >= 0x100000)
			{
				if (x >= 0x400000)
					xn = sqq_table[x>>16] << 4;
				else
					xn = sqq_table[x>>14] << 3;
			}
			else
			{
				if (x >= 0x40000)
					xn = sqq_table[x>>12] << 2;
				else
					xn = sqq_table[x>>10] << 1;
			}
			
			goto nr1;
		}
	}
	else if (x >= 0x100)
	{
		if (x >= 0x1000)
		{
			if (x >= 0x4000)
				xn = (sqq_table[x>>8] >> 0) + 1;
			else
				xn = (sqq_table[x>>6] >> 1) + 1;
		}
		else
		{
			if (x >= 0x400)
				xn = (sqq_table[x>>4] >> 2) + 1;
			else
				xn = (sqq_table[x>>2] >> 3) + 1;
		}

		goto adj;
	}
	else
		return (sqq_table[x] >> 4) << (FIXED_SHIFT / 2);

	xn = (xn + 1 + x / xn) / 2;
nr1:
	xn = (xn + 1 + x / xn) / 2;
adj:
	if (xn * xn > x)
		--xn;

	return xn << (FIXED_SHIFT / 2);
}
			
