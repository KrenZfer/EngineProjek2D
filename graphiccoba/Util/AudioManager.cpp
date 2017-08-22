#include "AudioManager.h"

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}

void AudioManager::Init()
{
	SoundEngine = createIrrKlangDevice();
	volume = 1.f;
	SoundEngine->setSoundVolume(volume);
}

void AudioManager::PlayBGM(char * audioPath)
{
	SoundEngine->play2D(audioPath, true);
}

void AudioManager::PlaySFX(char * audioPath)
{
	SoundEngine->play2D(audioPath, false);
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
