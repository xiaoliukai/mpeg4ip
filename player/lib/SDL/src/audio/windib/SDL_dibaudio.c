/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997, 1998, 1999, 2000, 2001  Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Sam Lantinga
    slouken@devolution.com
*/

#ifdef SAVE_RCSID
static char rcsid =
 "@(#) $Id: SDL_dibaudio.c,v 1.1 2001/04/10 23:45:02 cahighlander Exp $";
#endif

/* Allow access to a raw mixing buffer */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>

#include "SDL_audio.h"
#include "SDL_mutex.h"
#include "SDL_timer.h"
#include "SDL_audio_c.h"
#include "SDL_dibaudio.h"


/* Audio driver functions */
static int DIB_OpenAudio(_THIS, SDL_AudioSpec *spec);
static void DIB_ThreadInit(_THIS);
static void DIB_WaitAudio(_THIS);
static Uint8 *DIB_GetAudioBuf(_THIS);
static void DIB_PlayAudio(_THIS);
static void DIB_WaitDone(_THIS);
static void DIB_CloseAudio(_THIS);

/* Audio driver bootstrap functions */

static int Audio_Available(void)
{
	return(1);
}

static void Audio_DeleteDevice(SDL_AudioDevice *device)
{
	free(device->hidden);
	free(device);
}

static SDL_AudioDevice *Audio_CreateDevice(int devindex)
{
	SDL_AudioDevice *this;

	/* Initialize all variables that we clean on shutdown */
	this = (SDL_AudioDevice *)malloc(sizeof(SDL_AudioDevice));
	if ( this ) {
		memset(this, 0, (sizeof *this));
		this->hidden = (struct SDL_PrivateAudioData *)
				malloc((sizeof *this->hidden));
	}
	if ( (this == NULL) || (this->hidden == NULL) ) {
		SDL_OutOfMemory();
		if ( this ) {
			free(this);
		}
		return(0);
	}
	memset(this->hidden, 0, (sizeof *this->hidden));

	/* Set the function pointers */
	this->OpenAudio = DIB_OpenAudio;
	this->ThreadInit = DIB_ThreadInit;
	this->WaitAudio = DIB_WaitAudio;
	this->PlayAudio = DIB_PlayAudio;
	this->GetAudioBuf = DIB_GetAudioBuf;
	this->WaitDone = DIB_WaitDone;
	this->CloseAudio = DIB_CloseAudio;

	this->free = Audio_DeleteDevice;

	return this;
}

AudioBootStrap WAVEOUT_bootstrap = {
	"waveout", "Win95/98/NT/2000 WaveOut",
	Audio_Available, Audio_CreateDevice
};


/* The Win32 callback for filling the WAVE device */
static void CALLBACK FillSound(HWAVEOUT hwo, UINT uMsg, DWORD dwInstance,
						DWORD dwParam1, DWORD dwParam2)
{
	SDL_AudioDevice *this = (SDL_AudioDevice *)dwInstance;

	/* Only service "buffer done playing" messages */
	if ( uMsg != WOM_DONE )
		return;

	/* Signal that we are done playing a buffer */
	ReleaseSemaphore(audio_sem, 1, NULL);
}

static void SetMMerror(char *function, MMRESULT code)
{
	int len;
	char errbuf[MAXERRORLENGTH];

	sprintf(errbuf, "%s: ", function);
	len = strlen(errbuf);
	waveOutGetErrorText(code, errbuf+len, MAXERRORLENGTH-len);
	SDL_SetError("%s", errbuf);
}

/* Set high priority for the audio thread */
static void DIB_ThreadInit(_THIS)
{
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
}

void DIB_WaitAudio(_THIS)
{
	/* Wait for an audio chunk to finish */
	WaitForSingleObject(audio_sem, INFINITE);
}

Uint8 *DIB_GetAudioBuf(_THIS)
{
        Uint8 *retval;

	retval = (Uint8 *)(wavebuf[next_buffer].lpData);
	return retval;
}

void DIB_PlayAudio(_THIS)
{
	/* Queue it up */
	waveOutWrite(sound, &wavebuf[next_buffer], sizeof(wavebuf[0]));
	next_buffer = (next_buffer+1)%NUM_BUFFERS;
}

void DIB_WaitDone(_THIS)
{
	int i, left;

	do {
		left = NUM_BUFFERS;
		for ( i=0; i<NUM_BUFFERS; ++i ) {
			if ( wavebuf[i].dwFlags & WHDR_DONE ) {
				--left;
			}
		}
		if ( left > 0 ) {
			SDL_Delay(100);
		}
	} while ( left > 0 );
}

void DIB_CloseAudio(_THIS)
{
	int i;

	/* Close up audio */
	if ( audio_sem ) {
		CloseHandle(audio_sem);
	}
	if ( sound ) {
		waveOutClose(sound);
	}

	/* Clean up mixing buffers */
	for ( i=0; i<NUM_BUFFERS; ++i ) {
		if ( wavebuf[i].dwUser != 0xFFFF ) {
			waveOutUnprepareHeader(sound, &wavebuf[i],
						sizeof(wavebuf[i]));
			wavebuf[i].dwUser = 0xFFFF;
		}
	}
	/* Free raw mixing buffer */
	if ( mixbuf != NULL ) {
		free(mixbuf);
		mixbuf = NULL;
	}
}

int DIB_OpenAudio(_THIS, SDL_AudioSpec *spec)
{
	MMRESULT result;
	int i;
	WAVEFORMATEX waveformat;

	/* Initialize the wavebuf structures for closing */
	sound = NULL;
	audio_sem = NULL;
	for ( i = 0; i < NUM_BUFFERS; ++i )
		wavebuf[i].dwUser = 0xFFFF;
	mixbuf = NULL;

	/* Set basic WAVE format parameters */
	memset(&waveformat, 0, sizeof(waveformat));
	waveformat.wFormatTag = WAVE_FORMAT_PCM;

	/* Determine the audio parameters from the AudioSpec */
	switch ( spec->format & 0xFF ) {
		case 8:
			/* Unsigned 8 bit audio data */
			spec->format = AUDIO_U8;
			waveformat.wBitsPerSample = 8;
			break;
		case 16:
			/* Signed 16 bit audio data */
			spec->format = AUDIO_S16;
			waveformat.wBitsPerSample = 16;
			break;
		default:
			SDL_SetError("Unsupported audio format");
			return(-1);
	}
	waveformat.nChannels = spec->channels;
	waveformat.nSamplesPerSec = spec->freq;
	waveformat.nBlockAlign =
		waveformat.nChannels * (waveformat.wBitsPerSample/8);
	waveformat.nAvgBytesPerSec = 
		waveformat.nSamplesPerSec * waveformat.nBlockAlign;

	/* Check the buffer size -- minimum of 1/4 second (word aligned) */
	if ( spec->samples < (spec->freq/4) )
		spec->samples = ((spec->freq/4)+3)&~3;

	/* Update the fragment size as size in bytes */
	SDL_CalculateAudioSpec(spec);

	/* Open the audio device */
	result = waveOutOpen(&sound, WAVE_MAPPER, &waveformat,
			(DWORD)FillSound, (DWORD)this, CALLBACK_FUNCTION);
	if ( result != MMSYSERR_NOERROR ) {
		SetMMerror("waveOutOpen()", result);
		return(-1);
	}

#ifdef SOUND_DEBUG
	/* Check the sound device we retrieved */
	{
		WAVEOUTCAPS caps;

		result = waveOutGetDevCaps((UINT)sound, &caps, sizeof(caps));
		if ( result != MMSYSERR_NOERROR ) {
			SetMMerror("waveOutGetDevCaps()", result);
			return(-1);
		}
		printf("Audio device: %s\n", caps.szPname);
	}
#endif

	/* Create the audio buffer semaphore */
	audio_sem = CreateSemaphore(NULL, NUM_BUFFERS-1, NUM_BUFFERS, NULL);
	if ( audio_sem == NULL ) {
		SDL_SetError("Couldn't create semaphore");
		return(-1);
	}

	/* Create the sound buffers */
	mixbuf = (Uint8 *)malloc(NUM_BUFFERS*spec->size);
	if ( mixbuf == NULL ) {
		SDL_SetError("Out of memory");
		return(-1);
	}
	for ( i = 0; i < NUM_BUFFERS; ++i ) {
		memset(&wavebuf[i], 0, sizeof(wavebuf[i]));
		wavebuf[i].lpData = (LPSTR) &mixbuf[i*spec->size];
		wavebuf[i].dwBufferLength = spec->size;
		wavebuf[i].dwFlags = WHDR_DONE;
		result = waveOutPrepareHeader(sound, &wavebuf[i],
							sizeof(wavebuf[i]));
		if ( result != MMSYSERR_NOERROR ) {
			SetMMerror("waveOutPrepareHeader()", result);
			return(-1);
		}
	}

	/* Ready to go! */
	next_buffer = 0;
	return(0);
}