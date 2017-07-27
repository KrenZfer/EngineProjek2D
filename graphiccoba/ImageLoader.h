#ifndef _H_IMAGE_LOADER_H_
#define _H_IMAGE_LOADER_H_

#include <SOIL\SOIL.h>
#include <iostream>
#include <string>
#include "ImageTexture.h"
#include "GLSLProgram.h"

using namespace std;

namespace EngineProject2D {
	
	class ImageLoader {

	public:
		static ImageTexture imageLoad(const char* imagePath);
	};

}


#endif // !_H_IMAGE_LOADER_H_

