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
	batch.Init();
	//KrenZfer = Person(vec2(400.0f, 300.0f), 1.0f, false, m_camera, &inputManager);
	//KrenZfer.init("Texture/cup.png");
	Robin = Player(vec2(100.0f, 100.0f), 1.0f, m_camera, &inputManager);
	Robin.init("Texture/alien.png");
}

void MainGame::Update(float deltaTime)
{
	m_camera.update();
	//KrenZfer.update(m_camera, deltaTime);
	Robin.checkUpdate(KrenZfer.s_human);
	Robin.update(m_camera, deltaTime);
	//cout << "deltaTime : " << deltaTime << endl;
}

void MainGame::Render()
{
	glClearDepth(1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	batch.begin();

	//KrenZfer.draw(&batch);
	Robin.draw(&batch);

	batch.end();

	batch.renderBatch();
}

