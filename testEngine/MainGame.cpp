#include "MainGame.h"



MainGame::MainGame() : screenWidth(800), screenHeight(600)
{
	
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	init();
	update();
}

void MainGame::init()
{
	EngineProject2D::init();

	g_window.createWindow("Coba", screenWidth, screenHeight, true, EngineProject2D::WindowManager::WINDOWED);
}

void MainGame::update() {
	int l;
	while (true) {
		cout << "runnning State" << endl;
		cin >> l;
		SDL_Quit();
		exit(0);
	}
}
