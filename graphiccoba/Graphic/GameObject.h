#ifndef _H_GAME_OBJECT_H_
#define _H_GAME_OBJECT_H_

#include "Sprite.h"
#include "SpriteBatch.h"
#include "Rectangle.h"

using namespace EngineProject2D;

class GameObject {
	
public:
	//GameObject(){}
	GameObject(Sprite sprite, string _TAG = "OBJECT") {
		Object_Sprite = sprite;
		TAG = _TAG;
	}
	~GameObject(){}

	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw(SpriteBatch *batch) = 0;
	Sprite getSprite() { return Object_Sprite; }
	string getTAG() { return TAG; }
	void setTAG(string _TAG) { TAG = _TAG; }
	void setSprite(Sprite sprite) {
		Object_Sprite = sprite;
	}
	Sprite Object_Sprite;

protected:

	
	string TAG;
	Rectangle collider;

	bool collidesCheck(GameObject *object) {
		//AABB Collision Method has to improve in future development
		collider.setPosition(Object_Sprite.getPosition());
		collider.setSize(Object_Sprite.getSize());
		return collider.collidesWith(object);
		/*if (this->Object_Sprite.getPosition().x < object->getSprite().getPosition().x + object->getSprite().getSize().x &&
			this->Object_Sprite.getPosition().y < object->getSprite().getPosition().y + object->getSprite().getSize().y &&
			this->Object_Sprite.getPosition().x + this->Object_Sprite.getSize().x > object->getSprite().getPosition().x &&
			this->Object_Sprite.getPosition().y + this->Object_Sprite.getSize().y > object->getSprite().getPosition().y
			) {
			return true;
		}
		return false;*/
	}
};


#endif // !_H_GAME_OBJECT_H_

