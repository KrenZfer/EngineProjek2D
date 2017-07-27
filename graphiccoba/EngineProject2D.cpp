#include "EngineProject2D.h"

int EngineProject2D::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	return 0;
}
