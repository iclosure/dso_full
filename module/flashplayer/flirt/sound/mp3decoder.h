/*
 Flirt, an SWF rendering library
 Copyright (c) 2004-2006 Dave Hayden <dave@opaque.net>
 All rights reserved.
 
 http://www.opaque.net/flirt/

 This code is distributed under the two-clause BSD license.
 Read the LICENSE file or visit the URL above for details
*/

#ifndef DD_SOUND_MP3DECODE_H_INCLUDED
#define DD_SOUND_MP3DECODE_H_INCLUDED

#include "../dd.h"

typedef struct _ddMP3Decoder ddMP3Decoder;

#include "mad.h"
#include "mixer.h"
#include "../player/sound.h"


#if defined(WIN32)
// Visual Studio C 6++ ->
#pragma warning( disable : 4244 )  // Disable warning messages in simulation
#pragma warning( disable : 4761 )  // Disable warning "integral size mismatch in argument; conversion supplied"
#pragma warning( disable : 4305)   // truncation from 'const double ' to 'float '
#pragma warning( disable : 4049)   // compiler limit : terminating line number emission
// Visual Studio 2008 ->
#pragma warning( disable : 4996)   // 'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
#endif 


struct _ddMP3Decoder
{
	struct mad_stream stream;
	struct mad_frame frame;
	struct mad_synth synth;
	int a ; 
};


ddMP3Decoder*
dd_newMP3Decoder();

void
dd_destroyMP3Decoder(ddMP3Decoder* decoder);

boolean
ddMP3Decoder_decodeFrame(ddMP3Decoder* decoder, ddSoundTransform xform, unsigned char** dataPtr, int datalength, int delay, ddAudioSample** bufferPtr, int size);

#endif /* DD_SOUND_MP3DECODE_H_INCLUDED */
