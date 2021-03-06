/*
 Flirt, an SWF rendering library
 Copyright (c) 2004-2006 Dave Hayden <dave@opaque.net>
 All rights reserved.
 
 http://www.opaque.net/flirt/

 This code is distributed under the two-clause BSD license.
 Read the LICENSE file or visit the URL above for details
*/

#ifndef DD_SOUND_MIXER_H_INCLUDED
#define DD_SOUND_MIXER_H_INCLUDED

#include "../dd.h"


#if defined(WIN32)
// Visual Studio C 6++ ->
#pragma warning( disable : 4244 )  // Disable warning messages in simulation
#pragma warning( disable : 4761 )  // Disable warning "integral size mismatch in argument; conversion supplied"
#pragma warning( disable : 4305)   // truncation from 'const double ' to 'float '
#pragma warning( disable : 4049)   // compiler limit : terminating line number emission
// Visual Studio 2008 ->
#pragma warning( disable : 4996)   // 'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
#endif 

// Eight channels of simultaneous stereo

typedef struct _ddSoundMixer ddSoundMixer;
typedef struct _ddPlayingSound ddPlayingSound;

typedef struct
{
	int left;
	int right;
} ddAudioSample;

#include "../player/player.h"
#include "../sound/mp3decoder.h"

#define DD_SAMPLE_MAX_POS 0x0000ffff
#define DD_SAMPLE_MAX_NEG 0xffff8000

#define DD_SAMPLE_SINT16(s) \
	(SInt16)(((s)>DD_SAMPLE_MAX_POS)?0x7fff:(((s)<DD_SAMPLE_MAX_NEG)?0x8000:(s)))

struct _ddPlayingSound
{
	ddPlayingSound* next;
	
	ddSoundInstance* sound;
	ddDrawClip* clip;
	
	ddSoundTransform xform;
	int offset;
	int loopCount;

	ddMP3Decoder* decoder;
	int delay;
};

struct streamingSound
{
	struct streamingSound* next;
	ddSoundStreamBlock* block;
	ddDrawClip* clip;
};


struct _ddSoundMixer
{
	ddPlayingSound* sounds;
	struct streamingSound* streams;

	boolean playing;
};

ddSoundMixer*
dd_newSoundMixer();

void
dd_destroySoundMixer(ddSoundMixer*);

boolean
ddSoundMixer_renderFrameIntoBuffer(ddSoundMixer* mixer, ddAudioSample* buffer, int* ioSize);

void
ddSoundMixer_playSoundStreamBlock(ddSoundMixer* mixer, ddDrawClip* clip, ddSoundStreamBlock* block);

ddPlayingSound*
ddSoundMixer_playSoundInstance(ddSoundMixer* mixer, ddDrawClip* clip, ddSoundInstance* sound);

void
ddSoundMixer_stopSoundInstance(ddSoundMixer* mixer, ddSoundInstance* sound);

void
ddSoundMixer_clearStreamBlocks(ddSoundMixer* mixer);

#endif /* DD_MIXER_H_INCLUDED */
