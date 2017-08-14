#include "WindowManager.h"

EngineProject2D::WindowManager::WindowManager(){}

EngineProject2D::WindowManager::~WindowManager()
{
	
}

int EngineProject2D::WindowManager::createWindow(string windowName, int screenWidth, int screenHeight, bool vsync, WindowFlag selectFlag)
{
	if (selectFlag == WindowFlag::BORDERLESS) {
		flags |= SDL_WINDOW_BORDERLESS;
	}
	if (selectFlag == WindowFlag::EXCLUSIVE_FULLSCREEN) {
		flags |= SDL_WINDOW_FULLSCREEN;
	}
	if (selectFlag == WindowFlag::FULLSCREEN) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->screenWidth, this->screenHeight, flags);
	if (window == nullptr) {
		ErrorHandling::fatalError("Failed to Create SDL Window!!");
	}

	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (context == nullptr) {
		ErrorHandling::fatalError("Failed to Create SDL_GL CONTEXT!!");
	}

	glewExperimental = GL_TRUE;
	GLenum glewStat = glewInit();
	if (glewStat != GLEW_OK) {
		ErrorHandling::fatalError("Failed to Initiate GLEW!!");
	}
	cout << "OPENGL Version : " << glGetString(GL_VERSION) << endl;
	cout << "GLSL Version : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
	glClearColor(1, 0, 0, 0);

	SDL_GL_SetSwapInterval(vsync);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, screenWidth, screenHeight);

	return 0;
}

void EngineProject2D::WindowManager::swapBuffer()
{
	SDL_GL_SwapWindow(window);
}

int EngineProject2D::WindowManager::getScreenWidth()
{
	return screenWidth;
}

int EngineProject2D::WindowManager::getScreenHeight()
{
	return screenHeight;
}






