#include "../Core/GameCore.h"

GameCore::GameCore() : screenWidth(800), screenHeight(600) {
}

GameCore::~GameCore() {
}

void GameCore::Run(string windowTitle, int _screenWidth, int _screenHeight, bool vsync, WindowManager::WindowFlag flag, unsigned int _targetFrame, unsigned int _timeScale) {
	EngineProject2D::init();

	screenWidth = checkScreenWidth(_screenWidth);
	screenHeight = checkScreenHeight(_screenHeight);
	targetFrame = _targetFrame;
	timeScale = _timeScale;

	timingFPS.init(targetFrame, timeScale);
	winManager.createWindow(windowTitle, screenWidth, screenHeight, vsync, flag);
	state = GameState::RUNNING;
	Loop();
}

void GameCore::Loop()
{
	Init();
	while (state != GameState::EXIT) {
		float deltaTime = timingFPS.GetDeltaTime();
		PollInput();
		timingFPS.update();
		Update(deltaTime);
		Render();

		winManager.swapBuffer();
	}

}

void GameCore::PollInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) { 
		switch (event.type) {
		case SDL_QUIT:
			state = GameState::EXIT;
		case SDL_KEYDOWN:
			inputManager.PressKey(event.key.keysym.sym);
		case SDL_KEYUP:
			inputManager.ReleaseKey(event.key.keysym.sym);
		case SDL_MOUSEBUTTONDOWN:
			inputManager.PressKey(event.key.keysym.sym);
		case SDL_MOUSEBUTTONUP:
			inputManager.ReleaseKey(event.key.keysym.sym);
		}
	}
}

int GameCore::checkScreenHeight(int sHeight)
{
	if (sHeight > 0) {
		return sHeight;
	}
	else {
		return 600;
	}
}

int GameCore::checkScreenWidth(int sWidth)
{
	if (sWidth > 0) {
		return sWidth;
	}
	else {
		return 800;
	}
}