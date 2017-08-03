#ifndef _H_IO_MANAGER_H_
#define _H_IO_MANAGER_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

namespace EngineProject2D {

	class IOManager {

	public:
		static bool readFiletoBuffer(const char* filepath, string& textFile);
	};

}


#endif // !_H_IO_MANAGER_H_

