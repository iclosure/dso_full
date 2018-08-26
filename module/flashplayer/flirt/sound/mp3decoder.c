/*
 Flirt, an SWF rendering library
 Copyright (c) 2004-2006 Dave Hayden <dave@opaque.net>
 All rights reserved.
 
 http://www.opaque.net/flirt/

 This code is distributed under the two-clause BSD license.
 Read the LICENSE file or visit the URL above for details
*/

#include "mp3decoder.h"

#ifdef HAVE_MAD

//#include "mad.h"

#if defined(WIN32)
// Visual Studio C 6++ ->
#pragma warning( disable : 4244 )  // Disable warning messages in simulation
#pragma warning( disable : 4761 )  // Disable warning "integral size mismatch in argument; conversion supplied"
#pragma warning( disable : 4305)   // truncation from 'const double ' to 'float '
#pragma warning( disable : 4049)   // compiler limit : terminating line number emission
// Visual Studio 2008 ->
#pragma warning( disable : 4996)   // 'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
#endif 


ddMP3Decoder*
dd_newMP3Decoder()
{
	
	ddMP3Decoder* decoder = dd_malloc(sizeof(ddMP3Decoder));
	mad_stream_init(&decoder->stream);
	mad_frame_init(&decoder->frame);
	mad_synth_init(&decoder->synth);
	
	return decoder;
}

void
dd_destroyMP3Decoder(ddMP3Decoder* decoder)
{
	mad_synth_finish(&decoder->synth);
	mad_frame_finish(&decoder->frame);
	mad_stream_finish(&decoder->stream);

	dd_free(decoder);
}


boolean
ddMP3Decoder_decodeFrame(ddMP3Decoder* decoder, ddSoundTransform xform, unsigned char** dataPtr, int datalength, int delay, ddAudioSample** bufferPtr, int size)
{
	struct mad_pcm* pcm;
	int samplerate,length,i,stereo,left,right; 
	ddAudioSample* buffer = *bufferPtr;
	unsigned char* data = *dataPtr;
	
	mad_stream_buffer(&decoder->stream, data, datalength);
	
	if ( mad_frame_decode(&decoder->frame, &decoder->stream) < 0 )
		return DD_FALSE;
	
	mad_synth_frame(&decoder->synth, &decoder->frame);
	
	pcm = &decoder->synth.pcm;
	
	samplerate = pcm->samplerate;
	length = pcm->length;
	
	i = 0;
	stereo = (pcm->channels == 2);
	
	for ( i = 0; i < length; ++i )
	{
		left = pcm->samples[0][i];
		right = pcm->samples[1][i];
		
		buffer->left += left * xform.leftToLeft + right * xform.rightToLeft;
		buffer->right += left * xform.leftToRight + right * xform.rightToRight;
		++buffer;
	}

	*dataPtr = (unsigned char*)decoder->stream.next_frame;
	*bufferPtr = buffer;
	return DD_TRUE;
}

#else

ddMP3Decoder*
dd_newMP3Decoder()
{
	return NULL;
}

void
dd_destroyMP3Decoder(ddMP3Decoder* decoder)
{
}

int
ddMP3Decoder_decodeFrame(ddMP3Decoder* decoder, ddSoundTransform xform, unsigned char** dataPtr, int datalength, int delay, ddAudioSample** bufferPtr, int size)
{
	return 0;
}

#endif /* HAVE_MAD */
