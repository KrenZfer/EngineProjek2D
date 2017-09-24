#include "MainGame.h"

MainGame::MainGame() 
{
	
}

MainGame::~MainGame()
{
}

MainMenu *MainMenu::menuInstance;
CreditMenu *CreditMenu::creditInstance;
//GameMenu *GameMenu::gameInstance;

void MainGame::Init()
{
	m_camera.init(screenWidth, screenHeight);
	m_camera.setPosition(vec2(0.0f, 0.0f));
	l_program.BuildShader("Shaders/spriteShader.vert", "Shaders/spriteShader.frag");
	batch.Init();
	instanceMain = MainMenu::instance(&stateManager, &m_camera, &inputManager, &winManager);
	stateManager.pushState(instanceMain);
}

void MainGame::Update(float deltaTime)
{
	m_camera.update();
	stateManager.getStateStack().back()->Update(deltaTime);
}

void MainGame::Render()
{
	glClearDepth(1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	l_program.useShader();

	//input projection
	GLint projloc = l_program.getUniformLocation("projection");
	mat4 projection = m_camera.getCameraMatrix();
	glUniformMatrix4fv(projloc, 1, GL_FALSE, value_ptr(projection));

	//input sampler
	GLint samplerloc = l_program.getUniformLocation("texture0");
	glUniform1i(samplerloc, 0);
	
	batch.begin(GlyphSortType::BACK_TO_FRONT);

	stateManager.getStateStack().back()->Draw(batch);

	batch.end();

	batch.renderBatch();
}

