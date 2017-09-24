#ifndef _H_GLASS_H_
#define _H_GLASS_H_

#include <Graphic\Sprite.h>
#include <Graphic\SpriteBatch.h>
#include <Graphic\Animation.h>
#include <Graphic\GameObject.h>

#define SPOT_POWER 3;

using namespace EngineProject2D;

class Glass : public GameObject {

public:
	Glass(Sprite sprite) : GameObject(Sprite("GLASS"), "GLASS") {
		Object_Sprite = sprite;
		isAnySpot = false;
		spotPower = SPOT_POWER;
		counterBersih = 1;
	}
	~Glass(){}

	void init() override;

	void update(float deltaTime) override;

	void draw(SpriteBatch *batch) override;

	void setSpot(bool isSpot) {
		isAnySpot = isSpot;
		if (isAnySpot) {
			spot = Sprite("SPOT");
			spot.init(Object_Sprite.getPosition(), Object_Sprite.getScale(), "Texture/spot.png", 5.0f);
		}
		spotAnim = Animation("SPOT");
		spotAnim.createKeyFrame(spot, 1, 3);
	}

	bool getSpot() { return isAnySpot; }

	void eraseSpot() {
		counterBersih++;
		if (counterBersih % 60 == 0 && spotPower > 0) {
			spotPower--;
		}
		if (counterBersih > 300) {
			counterBersih = 1;
		}
	}
	vec2 getPosition() { return spot.getPosition(); }

private:
	int counterBersih;
	Animation spotAnim;
	KeyFrame currentFrame;
	//Sprite glass;
	Sprite spot;
	int spotPower;
	bool isAnySpot;

};

#endif // !_H_GLASS_H_

