#include "ResourceManager.h"

namespace EngineProject2D {

	TextureCache ResourceManager::textureCache;
	AudioCache ResourceManager::audioCache;

	ImageTexture ResourceManager::getImageTexture(const char * filePath)
	{
		return textureCache.getImageTexture(filePath);
	}

	AudioManager ResourceManager::getAudioData(const char * filePath, bool _loop)
	{
		return audioCache.getAudioData(filePath, _loop);
	}

}