#include "AudioHandling.h"

AudioHandling::AudioHandling(const char* music)
{
	MP3NAME = music;
}

AudioHandling::~AudioHandling()
{
}

void AudioHandling::InitMusic()
{
	SoundEngine = createIrrKlangDevice();
}

void AudioHandling::PlayMusic(bool loop)
{
	if (loop) {
		SoundEngine->play2D(MP3NAME, GL_TRUE);
	}
	else {
		SoundEngine->play2D(MP3NAME, GL_FALSE);
	}
}
