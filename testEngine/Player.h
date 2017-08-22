#ifndef _H_PLAYER_H_
#define _H_PLAYER_H_

#include "Person.h"

class Player : public Person {

public:
	Player();
	Player(vec2 Position, float scale, Camera camera, InputManager *inputManager);
	~Player();

	virtual void checkInput(float deltaTime) override;
	void checkUpdate(Sprite sprite);

private:
	vec2 s_displacement;
	vec2 prev_position;
	int in;


};

#endif // !_H_PLAYER_H_