#ifndef _H_AUDIO_MANAGER_H_
#define _H_AUDIO_MANAGER_H_

#include <irrKlang\irrKlang.h>

using namespace irrklang;

namespace EngineProject2D {
	class AudioManager {

	public:
		AudioManager();
		~AudioManager();

		void Init(const char* audioPath, bool _loop);
		void Play();
		void Stop();
		void Pause();
		void Mute();
		void Unmute();

		void setVolume(float _volume) { 
			volume = _volume; 
			SoundEngine->setSoundVolume(volume);
		}

		ISound* getISound() { return iSound; }

	private:
		float volume;
		ISoundEngine *SoundEngine;
		const char* audioPath;
		bool loop;
		ISound *iSound;


	};
}

#endif // !_H_AUDIO_MANAGER_H_

