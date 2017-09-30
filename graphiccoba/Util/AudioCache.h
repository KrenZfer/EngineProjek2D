#ifndef _H_AUDIO_CACHE_H_
#define _H_AUDIO_CACHE_H_

#include <unordered_map>
#include "AudioManager.h"

using namespace std;

namespace EngineProject2D {

	class AudioCache {

	public:
		AudioCache();
		~AudioCache();

		AudioManager getAudioData(const char* filePath, bool _loop);

	private:
		unordered_map<const char*, AudioManager>audioData;

	};

}

#endif // !_H_AUDIO_CACHE_H_

