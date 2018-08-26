/*
 Flirt, an SWF rendering library
 Copyright (c) 2004-2006 Dave Hayden <dave@opaque.net>
 All rights reserved.
 
 http://www.opaque.net/flirt/

 This code is distributed under the two-clause BSD license.
 Read the LICENSE file or visit the URL above for details
*/

#include "raster.h"
#include "image.h"
#include "fill.h"
#include "cxform.h"
#include "alphablend.h"


#if defined(WIN32)
// Visual Studio C 6++ ->
#pragma warning( disable : 4244 )  // Disable warning messages in simulation
#pragma warning( disable : 4761 )  // Disable warning "integral size mismatch in argument; conversion supplied"
#pragma warning( disable : 4305)   // truncation from 'const double ' to 'float '
#pragma warning( disable : 4049)   // compiler limit : terminating line number emission
// Visual Studio 2008 ->
#pragma warning( disable : 4996)   // 'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
#endif 

void
tiledBitmapRaster(ddColor* buffer, ddFillInstance* fill, int y, ddCXform cXform)
{
	UInt32* alpha = fill->alphaBuffer;
	int left = fill->left;
	int right = fill->right;
	int x = left;

	ddImage* bitmap = fill->fill.data.bitmap.image;
	ddMatrix matrix = fill->inverse;
	ddColor color;

	fixed px, py, dpx, dpy;

	px = FIXED_I(x);
	py = FIXED_I(y);

	ddMatrix_apply(matrix, &px, &py);

	dpx = matrix.a;
	dpy = matrix.c;

	// XXX - any optimizations we can do if dpy == 0?

	if ( CXFORM_ISEMPTY(cXform) )
	{
		for ( x = left; x < right; ++x )
		{
			UInt8 c = alpha[x] >> (ALPHABUF_SHIFT-8);
			//color = ddImage_getTiledPixel_nearest(bitmap, px, py);
			color = ddImage_getTiledPixel_blended(bitmap, px, py);
			
			if ( c == 0xff )
				buffer[x] = color;
			else
				buffer[x] += ddColor_scale(color, c);
			
			px += dpx;
			py += dpy;
		}
	}
	else
	{
		for ( x = left; x < right; ++x )
		{
			UInt8 c = alpha[x] >> (ALPHABUF_SHIFT-8);
			//color = ddImage_getTiledPixel_nearest(bitmap, px, py);
			color = ddImage_getTiledPixel_blended(bitmap, px, py);
			color = ddCXform_applyPremultiplied(cXform, color);

			if ( c == 0xff )
				buffer[x] = color;
			else
				buffer[x] += ddColor_scale(color, c);
			
			px += dpx;
			py += dpy;
		}
	}
}


void
clippedBitmapRaster(ddColor* buffer, ddFillInstance* fill, int y, ddCXform cXform)
{
	UInt32* alpha = fill->alphaBuffer;
	int left = fill->left;
	int right = fill->right;
	int x = left;

	ddImage* bitmap = fill->fill.data.bitmap.image;
	ddMatrix matrix = fill->inverse;
	ddColor color = (ddColor)0;

	fixed px, py, dpx, dpy;

	px = FIXED_I(x);
	py = FIXED_I(y);

	ddMatrix_apply(matrix, &px, &py);

	dpx = matrix.a;
	dpy = matrix.c;

	if ( CXFORM_ISEMPTY(cXform) )
	{
		for ( x = left; x < right; ++x )
		{
			UInt8 c = alpha[x] >> (ALPHABUF_SHIFT-8);
			color = ddImage_getClippedPixel_blended(bitmap, px, py);
			//color = ddImage_getClippedPixel_nearest(bitmap, px, py);
			
			if ( c == 0xff )
				buffer[x] = color;
			else
				buffer[x] += ddColor_scale(color, c);
			
			px += dpx;
			py += dpy;
		}
	}
	else
	{
		for ( x = left; x < right; ++x )
		{
			UInt8 c = alpha[x] >> (ALPHABUF_SHIFT-8);
			color = ddImage_getClippedPixel_blended(bitmap, px, py);
			//color = ddImage_getClippedPixel_nearest(bitmap, px, py);
			color = ddCXform_applyPremultiplied(cXform, color);

			if ( c == 0xff )
				buffer[x] = color;
			else
				buffer[x] += ddColor_scale(color, c);
			
			px += dpx;
			py += dpy;
		}
	}
}
