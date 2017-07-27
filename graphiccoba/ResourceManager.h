#ifndef _H_RESOURCE_MANAGER_H_
#define _H_RESOURCE_MANAGER_H_

#include "ImageTexture.h"
#include "TextureCache.h"

namespace EngineProject2D {

	class ResourceManager {

	public:
		static ImageTexture getImageTexture(const char* filePath);

	private:
		static TextureCache textureCache;

	};


}

#endif // !_H_RESOURCE_MANAGER_H_

