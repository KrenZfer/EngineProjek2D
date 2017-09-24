#ifndef _H_POWER_BUFF_H_
#define _H_POWER_BUFF_H_

#include <string>
#include <Graphic\Sprite.h>
#include <Graphic\GameObject.h>
#include <Graphic\Animation.h>

//#include "Player.h"

class Player;

using namespace std;
using namespace EngineProject2D;

class PowerBuff : public GameObject {

public:
	enum POWER_UP {BURGER, SODA};
	enum POWER_DOWN {ICE_CUBE, BEER};

	PowerBuff() : GameObject(Sprite("POWER"), "POWER") {
		PowerBuff(POWER_UP::BURGER, vec2(0.0f));
	}
	PowerBuff(POWER_UP power, vec2 position);
	PowerBuff(POWER_DOWN power, vec2 position);
	~PowerBuff();

	void init() override;
	void update(float deltaTime)  override;

	void activateBuff(Player *player);
	void updatePosition(vec2 position) { pb_position = position; }
	void draw(SpriteBatch *batch) override;

	string getPBStatus() { return pb_status; }
	vec2 getPosition() { return pb_position; }
	bool isActivated() { return hasActivated; }

private:
	void freeFalling(float deltaTime) { pb_position.y -= pb_speed * deltaTime; }

	unsigned int pb_time;
	string pb_status = "";
	const char* texturePath;
	int animcol;
	int animrow;
	bool hasActivated;
	float pb_speed;
	Animation buffAnim;
	KeyFrame currentKey;

	/*Sprite pb_sprite;*/
	vec2 pb_position;

};


#endif // !_H_POWER_BUFF_H_


