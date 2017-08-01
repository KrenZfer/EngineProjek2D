#ifndef _H_MAIN_GAME_H_
#define _H_MAIN_GAME_H_
#include <WindowManager.h>
#include <EngineProject2D.h>

using namespace EngineProject2D;

class MainGame {

public:
	MainGame();
	~MainGame();
	void run();
	void init();
	void update();

	int screenWidth;
	int screenHeight;
	
	WindowManager g_window;

};

#endif // !_H_MAIN_H_

