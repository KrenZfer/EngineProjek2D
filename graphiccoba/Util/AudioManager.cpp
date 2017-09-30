#include "AudioManager.h"
namespace EngineProject2D {
	AudioManager::AudioManager()
	{
	}

	AudioManager::~AudioManager()
	{
	}

	void AudioManager::Init(const char * audioPath, bool _loop)
	{
		SoundEngine = createIrrKlangDevice();
		volume = 1.f;
		SoundEngine->setSoundVolume(volume);
		this->audioPath = audioPath;
		loop = _loop;
	}

	void AudioManager::Play()
	{
		iSound = SoundEngine->play2D(audioPath, loop, false, false, E_STREAM_MODE::ESM_AUTO_DETECT, true);
	}

	void AudioManager::Stop()
	{
		SoundEngine->stopAllSounds();
	}

	void AudioManager::Pause()
	{
		SoundEngine->setAllSoundsPaused();
	}

	void AudioManager::Mute()
	{
		SoundEngine->setSoundVolume(0.f);
	}

	void AudioManager::Unmute()
	{
		SoundEngine->setSoundVolume(volume);
	}

}