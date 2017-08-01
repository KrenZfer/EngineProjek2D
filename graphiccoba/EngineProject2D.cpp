#pragma once
#include "EngineProject2D.h"
#include <SDL\SDL.h>
#include <GL\glew.h>

namespace EngineProject2D {

	int EngineProject2D::init()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		return 0;
	}

}
