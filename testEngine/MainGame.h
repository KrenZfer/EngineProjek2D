#ifndef _H_MAIN_GAME_H_
#define _H_MAIN_GAME_H_

#include <Graphic\WindowManager.h>
#include <Graphic\EngineProject2D.h>
#include <Graphic\FontManager.h>
#include <Core\GameCore.h>
#include <Graphic\Camera.h>
#include <Graphic\SpriteBatch.h>
#include <Util\StateManager.h>

#include "Person.h"
#include "Player.h"
#include "Level.h"
#include "MainMenu.h"
#include "CreditMenu.h"
#include "GameMenu.h"


using namespace EngineProject2D;

class MainGame : public GameCore{
	
public:
	MainGame();
	~MainGame();

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();

	GLSLProgram* getGameShaderProgram() { return &l_program; }

private:

	GLSLProgram l_program;

	Camera m_camera;
	SpriteBatch batch;
	Level level1;
	StateManager stateManager;
	MainMenu *instanceMain;

};

#endif // !_H_MAIN_H_

