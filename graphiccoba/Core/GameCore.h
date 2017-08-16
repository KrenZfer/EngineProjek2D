#ifndef _H_GAME_CORE_H_
#define _H_GAME_CORE_H_


#include "../Graphic/EngineProject2D.h"
#include "../Graphic/WindowManager.h"
#include "../Core/Timing.h"
#include "../Core/InputManager.h"

using namespace std;
using namespace EngineProject2D;

enum class GameState { RUNNING, PAUSE, EXIT };

class GameCore {

public:
	GameCore();
	~GameCore();
	
	void Run(string windowTitle, int _screenWidth, int _screenHeight, bool vsync, WindowManager::WindowFlag flag = WindowManager::WindowFlag::WINDOWED, unsigned int _targetFrame = 60, unsigned int _timeScale = 1);
	void Loop();
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;

private:
	void PollInput();
	int checkScreenHeight(int sHeight);
	int checkScreenWidth(int sWidth);

protected:
	unsigned int targetFrame, timeScale;
	int screenHeight, screenWidth;
	Timing timingFPS;
	WindowManager winManager;
	GameState state;
	InputManager inputManager;


};

#endif // !_H_MAIN_GAME_H_
