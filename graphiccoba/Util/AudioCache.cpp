#include "AudioCache.h"

EngineProject2D::AudioCache::AudioCache()
{
}

EngineProject2D::AudioCache::~AudioCache()
{
}

EngineProject2D::AudioManager EngineProject2D::AudioCache::getAudioData(const char * filePath, bool _loop)
{
	unordered_map<const char*, AudioManager>::iterator it = audioData.find(filePath);

	if (it == audioData.end()) {

		AudioManager newAudio;
		newAudio.Init(filePath, _loop);
		audioData.insert(make_pair(filePath, newAudio));

		//cout << "Load New Texture" << endl;

		return newAudio;
	}

	//cout << "Used Cache Teture" << endl;

	return it->second;
}
