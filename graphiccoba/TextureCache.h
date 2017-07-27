#ifndef _H_TEXTURE_CACHE_H_
#define _H_TEXTURE_CACHE_H_

#include <string>
#include <unordered_map>
#include "ImageTexture.h"
#include "ImageLoader.h"

using namespace std;

namespace EngineProject2D {

	class TextureCache {

	public:
		TextureCache();
		~TextureCache();

		ImageTexture getImageTexture(const char* filePath);

	private:
		unordered_map<const char*, ImageTexture> texturecache_map;
	};

}

#endif // !_H_TEXTURE_CACHE_H_

