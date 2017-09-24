#include "Rectangle.h"
#include "GameObject.h"

Rectangle::Rectangle()
{
	r_position = vec2(0.0f);
	r_size = vec2(0.0f);
	
}

Rectangle::Rectangle(vec2 position, vec2 size)
{
	r_position = position;
	r_size = size;
}

bool Rectangle::collidesWith(GameObject * object)
{
	return collidesWith(&object->getSprite());
}

bool Rectangle::collidesWith(Sprite * sprite)
{
	if (r_position.x < sprite->getPosition().x + sprite->getSize().x &&
		r_position.y < sprite->getPosition().y + sprite->getSize().y &&
		r_position.x + r_size.x > sprite->getPosition().x &&
		r_position.y + r_size.y > sprite->getPosition().y
		) {
		return true;
	}
	return false;
}

