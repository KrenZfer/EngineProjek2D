#include "MainGame.h"

MainGame::MainGame() 
{
	
}

MainGame::~MainGame()
{
}

void MainGame::Init()
{
	m_camera.init(screenWidth, screenHeight);
	m_camera.setPosition(vec2(0.0f, 0.0f));
	KrenZfer = Person(vec2(20.0f, 40.0f), 1.0f, m_camera, &
		inputManager);
	KrenZfer.init();
}

void MainGame::Update(float deltaTime)
{
	m_camera.update();
	checkInput();
	KrenZfer.update(m_camera, deltaTime);
	//cout << "deltaTime : " << deltaTime << endl;
}

void MainGame::Render()
{
	glClearDepth(1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	KrenZfer.draw();
}

void MainGame::checkInput()
{
	if (inputManager.isKeyPressed(SDLK_a)) {
		cout << "Menekan A : " << SDLK_a << endl;
	}
}

