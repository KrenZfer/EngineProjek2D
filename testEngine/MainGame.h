#ifndef _H_MAIN_GAME_H_
#define _H_MAIN_GAME_H_

#include <Graphic\WindowManager.h>
#include <Graphic\EngineProject2D.h>
#include <Graphic\FontManager.h>
#include <Core\GameCore.h>
#include <Graphic\Camera.h>
#include <Graphic\SpriteBatch.h>

#include "Person.h"
#include "Player.h"


using namespace EngineProject2D;

class MainGame : public GameCore{
	
public:
	MainGame();
	~MainGame();

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();

private:

	Person KrenZfer;
	Player Robin;
	Camera m_camera;
	SpriteBatch batch;

};

#endif // !_H_MAIN_H_

