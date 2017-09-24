#ifndef _H_OBSTACLE_H_
#define _H_OBSTACLE_H_

#include <Graphic\Sprite.h>
#include <Graphic\SpriteBatch.h>
#include <Graphic\Animation.h>
#include <Graphic\GameObject.h>

using namespace EngineProject2D;

#define BASE_SPEED 0.1f

class Obstacle : public GameObject {

public:

	enum OBSTACLE_TYPE {COMPUTER, COUCH, CLOSET};

	Obstacle(vec2 position, OBSTACLE_TYPE type);
	Obstacle() : GameObject(Sprite("OBSTACLE"), "OBSTACLE"){}
	~Obstacle();
	void init() override;
	void draw(SpriteBatch *batch) override;
	void update(float deltaTime) override;

	void setPosition(vec2 pos) { obs_position = pos; }
	void setPosition(float x, float y) { setPosition(vec2(x, y)); }
	vec2 getPosition() { return obs_position; }
	int getDestructPower() { return destruct_power; }
	void freeFalling(float deltaTime) { obs_position.y -= obs_speed * deltaTime; }

private:

	//Sprite obs_sprite;
	OBSTACLE_TYPE obs_type;
	Animation obstAnim;
	KeyFrame curKeyFrame;
	int destruct_power;
	vec2 obs_position;
	float obs_speed;
	int row, col;
	const char* texturePath;

};

#endif // !_H_OBSTACLE_H_

