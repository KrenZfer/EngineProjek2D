#ifndef _H_RESOURCE_MANAGER_H_
#define _H_RESOURCE_MANAGER_H_

#include "ImageTexture.h"
#include "TextureCache.h"
#include "../Util/AudioCache.h"
#include "../Util/AudioManager.h"

namespace EngineProject2D {

	class ResourceManager {

	public:
		static ImageTexture getImageTexture(const char* filePath);
		static AudioManager getAudioData(const char* filePath, bool _loop);

	private:
		static TextureCache textureCache;
		static AudioCache audioCache;

	};


}

#endif // !_H_RESOURCE_MANAGER_H_

