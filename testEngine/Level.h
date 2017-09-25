#ifndef _H_LEVEL_H_
#define _H_LEVEL_H_

#include <string>
#include <Graphic\IOManager.h>
#include <Graphic\Sprite.h>
#include <Graphic\Camera.h>
#include <Core\InputManager.h>
#include <Graphic\GLSLProgram.h>
#include <GLM\gtc\type_ptr.hpp>
#include <Graphic\UI\button.h>
#include "Player.h"
#include "Glass.h"
#include "Obstacle.h"
#include "PowerBuff.h"

using namespace EngineProject2D;

class Level {

public:
	Level() { 
		ignore = false;
	}
	~Level() { 
		/*Glasses.clear();
		Walls.clear();
		parts.clear();
		obstacles.clear();
		buffs.clear();
		glassInform.clear();
		textLevel.clear();
		widthBuilding = 0;
		heightBuilding = 0;
		indeks = ivec2(0);
		spotNum = 10;
		ignore = false;

		delete player;*/
	}

	void LoadLevel(const char* textPath);
	void LoadTest(const char* textPath);
	void init(const char* textPath, Camera *camera, InputManager *inputManager, int screenWidth, int screenHeight);
	void update(float deltaTime);
	void draw(SpriteBatch* batch);

	Player* getPlayer() { return player; }

	int getBuildingHeight() { return heightBuilding; }
	vector<int> getGlassInformation() { return glassInform; }

private:
	void initShader(const char* vertexPath, const char* fragmentPath);

	void generateObstacle(float deltaTime);
	void generatePowerBuff(float deltaTime);

	int randGenerator(int batas) {
		return rand() % batas;
	}

	string textLevel;
	vector<Glass> Glasses;
	vector<Sprite> Walls;
	vector<vector<char>> parts;
	Player *player;
	GLSLProgram l_program;
	Camera *l_camera;
	bool ignore;
	bool obstacleinit = true;
	ivec2 indeks = ivec2(0);

	vector<Obstacle> obstacles;
	vector<PowerBuff> buffs;

	Sprite Sky_Background;
	Sprite cityParalax0;
	Sprite trainAcc;
	Sprite bottomBuilding;
	Sprite topBuilding;
	Sprite cityParalax1;
	Sprite cityParalax2;

	vector<int> glassInform;

	int spotNum = 10;

	float widthBuilding;
	float heightBuilding;
	float buildingstartX;
	float buildingstartY;

	int l_screenHeight;
	int l_screenWidth;
	int counter;
	int trainFactor;
};


#endif // !_H_LEVEL_H_
