#ifndef _H_PLAYER_H_
#define _H_PLAYER_H_

#include "Person.h"
#include "Obstacle.h"
#include "PowerBuff.h"
#include "Glass.h"
#include "Graphic\Rectangle.h"

#define INVINCIBLE 1000

class Player : public Person {

public:

	enum PLAYER_STATUS{ALIVE, DEAD};

	Player(vec2 Position, const char* pathTexture, float scale, Camera *camera, InputManager &inputManager);
	~Player();

	virtual void checkInput(float deltaTime) override;
	void checkUpdate(GameObject *object);
	void setBoundary(vec4 boundary) { this->boundary = boundary; }
	void tookObstacleDamage(Obstacle *obs);

	void playerHeal();
	void playerSpeedUp(int time);
	void playerDrunk(int time);
	void playerFreeze(int time);

	int getPlayerHealth() { return player_HEALTH; }
	PLAYER_STATUS getPlayerStatus() { return status; }

private:
	vec2 prev_position;
	int player_HEALTH;
	int countInvcObs = 0;
	bool takeDamage;
	bool isDrunk;
	bool isFreeze;
	float drunkFactor;
	int drunkTime;
	int freezeTime;
	int speedUpTime;
	PLAYER_STATUS status;
	vector<PowerBuff> BuffStack;
	Rectangle colliderWiper;
	Rectangle bodyCollider;

	AudioManager wiperSound;
	AudioManager gondolaSound;
	AudioManager powerDownSound;
	AudioManager powerUpSound;
	AudioManager obstacleHit;

	bool waitforWipe;
	bool gondolaMove;
	bool waitforgondolaSound;

	vec2 temp, cameraTemp;

};

#endif // !_H_PLAYER_H_