#include "IOManager.h"

namespace EngineProject2D {

	bool IOManager::readFiletoBuffer(const char* filepath, string& textFile)
	{
		ifstream file;
		stringstream textStream;

		file.exceptions(ifstream::failbit | ifstream::badbit);

		try {
			file.open(filepath);
			textStream << file.rdbuf();

			file.close();
		}
		catch (ifstream::failure e) {
			//when error
			return false;
		}
		textFile = textStream.str();
		return true;
	}

}