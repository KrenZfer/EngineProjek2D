#ifndef _H_AUDIO_MANAGER_H_

#include <irrKlang\irrKlang.h>

using namespace irrklang;

class AudioManager {

public:
	AudioManager();
	~AudioManager();

	void Init();
	void PlayBGM(char* audioPath);
	void PlaySFX(char* audioPath);
	void Stop();
	void Pause();
	void Mute();
	void Unmute();

private:
	float volume;
	ISoundEngine *SoundEngine;

};

#endif // !_H_AUDIO_MANAGER_H_

