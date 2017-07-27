#include "TextureCache.h"

namespace EngineProject2D {
	TextureCache::TextureCache()
	{
	}

	TextureCache::~TextureCache()
	{
	}

	ImageTexture TextureCache::getImageTexture(const char* filePath)
	{
		unordered_map<const char*, ImageTexture>::iterator it = texturecache_map.find(filePath);

		if (it == texturecache_map.end()) {
			
			ImageTexture newTexture = ImageLoader::imageLoad(filePath);
			texturecache_map.insert(make_pair(filePath, newTexture));

			cout << "Load New Texture" << endl;

			return newTexture;
		}

		cout << "Used Cache Teture" << endl;

		return it->second;
	}

}


