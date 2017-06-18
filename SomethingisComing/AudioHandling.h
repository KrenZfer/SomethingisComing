#ifndef _H_AUDIO_HANDLING_H
#define _H_AUDIO_HANDLING_H

#include <irrKlang/irrKlang.h>
#include <GL\glew.h>
#include <string>

using namespace irrklang;
using namespace std;

class AudioHandling {

public:
	AudioHandling(const char* music);
	~AudioHandling();
	ISoundEngine *SoundEngine;
	const char* MP3NAME;
	void InitMusic();
	void PlayMusic(bool loop);
};

#endif // !_H_AUDIO_HANDLING_H

