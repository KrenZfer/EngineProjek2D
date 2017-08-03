#include "ResourceManager.h"

namespace EngineProject2D {

	TextureCache ResourceManager::textureCache;

	ImageTexture ResourceManager::getImageTexture(const char * filePath)
	{
		return textureCache.getImageTexture(filePath);
	}

}