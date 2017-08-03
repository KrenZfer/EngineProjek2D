#ifndef _H_WINDOW_MANAGER_H_
#define _H_WINDOW_MANAGER_H_

#include <SDL\SDL.h>
#include <string>
#include "ErrorHandling.h"
#include <GL\glew.h>

using namespace std;

namespace EngineProject2D {

	class WindowManager {

	public:
		enum WindowState {RUNNING, EXIT};
		enum WindowFlag {FULLSCREEN, BORDERLESS, EXCLUSIVE_FULLSCREEN, WINDOWED};

		WindowManager();
		~WindowManager();

		WindowState currentState;

		int createWindow(string windowName, int screenWidth, int screenHeight, bool vsync, WindowFlag selectFlag);
		void swapBuffer();
		int getScreenWidth();
		int getScreenHeight();


	private:
		WindowFlag defaultFlags = WindowFlag::FULLSCREEN;
		int screenWidth, screenHeight;
		Uint32 flags = SDL_WINDOW_OPENGL;
		WindowState defaultState = WindowState::RUNNING;
		SDL_Window* window;

	};

}


#endif // !_H_WINDOW_MANAGER_H_

