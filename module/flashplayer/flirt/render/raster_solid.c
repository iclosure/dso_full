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
solidRaster(ddColor* buffer, ddFillInstance* fill, int y, ddCXform cXform)
{
	UInt32* alpha = fill->alphaBuffer;
	int left = fill->left;
	int right = fill->right;
	int x;

	ddColor color = ddCXform_apply(cXform, fill->fill.data.color);

	color = ddColor_premultiply(color);
	
	// XXX - look at altivec for this
	
	for ( x = left; x < right; ++x )
	{
		UInt8 c = alpha[x] >> (ALPHABUF_SHIFT-8);

#ifdef DD_DEBUG
		if ( (unsigned int)c + COLOR_ALPHA(buffer[x]) > 0xff )
			dd_log("alpha > 0xff in line buffer!");
#endif
		if ( c == 0xff )
			buffer[x] = color;
		
		else if ( c > 0 )
		{
			if ( (unsigned int)c + COLOR_ALPHA(buffer[x]) > 0xff )
				c = 0xff - COLOR_ALPHA(buffer[x]);

			if ( c > 0 )
				buffer[x] += ddColor_scale(color, c);
		}
	}
}
