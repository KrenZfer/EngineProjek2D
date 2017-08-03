#ifndef _H_ERROR_HANDLING_H_
#define _H_ERROR_HANDLING_H_

#include <string>
#include <iostream>
#include <SDL\SDL.h>

using namespace std;

namespace EngineProject2D {

	class ErrorHandling {

	public:
		static void fatalError(string errorString);
		static void fatalError(string errorString, int delay);
	};

}

#endif // !_H_ERROR_HANDLING_H_

