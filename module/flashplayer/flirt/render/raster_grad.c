/*
 Flirt, an SWF rendering library
 Copyright (c) 2004-2006 Dave Hayden <dave@opaque.net>
 All rights reserved.
 
 http://www.opaque.net/flirt/

 This code is distributed under the two-clause BSD license.
 Read the LICENSE file or visit the URL above for details
*/

#include "raster.h"
#include "alphablend.h"
#include <math.h>

#if defined(WIN32)
// Visual Studio C 6++ ->
#pragma warning( disable : 4244 )  // Disable warning messages in simulation
#pragma warning( disable : 4761 )  // Disable warning "integral size mismatch in argument; conversion supplied"
#pragma warning( disable : 4305)   // truncation from 'const double ' to 'float '
#pragma warning( disable : 4049)   // compiler limit : terminating line number emission
// Visual Studio 2008 ->
#pragma warning( disable : 4996)   // 'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
#endif 

#define GRAD_SCALE ((16384 * FIXED_I(1)) / TWIPS_I(1))

void
linearGradientRaster(ddColor* buffer, ddFillInstance* fill, int y, ddCXform cXform)
{
	UInt32* alpha = fill->alphaBuffer;
	int left = fill->left;
	int right = fill->right;
	int x;

	ddGradient* grad = fill->fill.data.gradient.gradient;
	ddColor color;

	fixed dx;
	fixed px = FIXED_I(left);
	fixed py = FIXED_I(y);

	ddMatrix_apply(fill->inverse, &px, &py);
	dx = fill->inverse.a; /* specifically, (1,0) dot M_inv*(1,0) */

	if ( CXFORM_ISEMPTY(cXform) )
	{
		for ( x = left; x < right; ++x )
		{
			UInt8 c = alpha[x] >> (ALPHABUF_SHIFT-8);
			color = ddGradient_getColor(grad, (px + 65280) / 2);
			color = ddColor_premultiply(color);

			if ( c == 0xff )
				buffer[x] = color;
			else
				buffer[x] += ddColor_scale(color, c);
				//buffer[x] = alpha_blend(buffer[x], color, alpha[x]);
			
			px += dx;
		}
	}
	else
	{
		for ( x = left; x < right; ++x )
		{
			UInt8 c = alpha[x] >> (ALPHABUF_SHIFT-8);
			color = ddGradient_getColor(grad, px);
			color = ddCXform_apply(cXform, color);
			color = ddColor_premultiply(color);

			if ( c == 0xff )
				buffer[x] = color;
			else
				buffer[x] += ddColor_scale(color, c);
				//buffer[x] = alpha_blend(buffer[x], color, alpha[x]);
			
			px += dx;
		}
	}
}


void
radialGradientRaster(ddColor* buffer, ddFillInstance* fill, int y, ddCXform cXform)
{
	UInt32* alpha = fill->alphaBuffer;
	int left = fill->left;
	int right = fill->right;
	int x;
	
	ddGradient* grad = fill->fill.data.gradient.gradient;
	ddColor color = (ddColor)0; /* XXX */

	fixed d;
	fixed dpx, dpy;
	fixed px = FIXED_I(left);
	fixed py = FIXED_I(y);

	ddMatrix_apply(fill->inverse, &px, &py);

	d = FIXED_D(hypot(DOUBLE_F(px), DOUBLE_F(py)));
	
	dpx = fill->inverse.a;
	dpy = fill->inverse.c;

	if ( CXFORM_ISEMPTY(cXform) )
	{
		for ( x = left; x < right; ++x )
		{
			UInt8 c = alpha[x] >> (ALPHABUF_SHIFT-8);
			int tx = px >> (FIXED_SHIFT / 2);
			int ty = py >> (FIXED_SHIFT / 2);

			/*
			d += fixed_mult(dx, fixed_divide(x, d));

			// somewhat arbitrary, but it works:
			// XXX - there's a bit of glitching on the right of center
			if ( d < FIXED_I(4) )
				d = FIXED_I(4);
			 */
			d = fixed_sqrt((unsigned)(tx * tx + ty * ty)); // FIXED_D(hypot(DOUBLE_F(x), DOUBLE_F(y)));
			color = ddGradient_getColor(grad, d);
			color = ddColor_premultiply(color);
			
			if ( c == 0xff )
				buffer[x] = color;
			else
				buffer[x] += ddColor_scale(color, c);
				//buffer[x] = alpha_blend(buffer[x], color, alpha[x]);
			
			px += dpx;
			py += dpy;
		}
	}
	else
	{
		for ( x = left; x < right; ++x )
		{
			UInt8 c = alpha[x] >> (ALPHABUF_SHIFT-8);

			int tx = px >> (FIXED_SHIFT / 2);
			int ty = py >> (FIXED_SHIFT / 2);

			//d += fixed_mult(dx, fixed_divide(x, d));

			/* somewhat arbitrary, but it works: */
			//if ( d < FIXED_I(4) )
			//	d = FIXED_I(4);

			d = fixed_sqrt((unsigned)(tx * tx + ty * ty)); // FIXED_D(hypot(DOUBLE_F(x), DOUBLE_F(y)));

			color = ddGradient_getColor(grad, d);
			color = ddCXform_apply(cXform, color);
			color = ddColor_premultiply(color);

			if ( c == 0xff )
				buffer[x] = color;
			else
				buffer[x] += ddColor_scale(color, c);
				//buffer[x] = alpha_blend(buffer[x], color, alpha[x]);
			
			px += dpx;
			py += dpy;
		}
	}
}
