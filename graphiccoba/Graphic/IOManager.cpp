#include "IOManager.h"

namespace EngineProject2D {

	bool IOManager::readFiletoBuffer(const char* filepath, string* textFile)
	{
		ifstream file;
		stringstream textStream;

		file.exceptions(ifstream::failbit | ifstream::badbit);

		try {
			file.open(filepath);
			textStream << file.rdbuf();

			file.close();
			*textFile = textStream.str();
		}
		catch (ifstream::failure e) {
			//when error
			cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
			return false;
		}
		return true;
	}

}