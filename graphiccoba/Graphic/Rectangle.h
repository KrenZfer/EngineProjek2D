#ifndef _H_RECTANGLE_H_
#define _H_RECTANGLE_H_

#include "Sprite.h"
#include <GLM\glm.hpp>

using namespace EngineProject2D;

class GameObject;

class Rectangle {

public:

	Rectangle();

	Rectangle(vec2 position, vec2 size);

	~Rectangle(){
	}

	bool collidesWith(GameObject *object);

	bool collidesWith(Sprite* sprite);

	void setPosition(vec2 position) { r_position = position; }
	void setSize(vec2 size) { r_size = size; }
	vec2 getPosition() { return r_position; }
	vec2 getSize() { return r_size; }

private:
	vec2 r_position;
	vec2 r_size;
	
};


#endif // !_H_RECTANGLE_H_
