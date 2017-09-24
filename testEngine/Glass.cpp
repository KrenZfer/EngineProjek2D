#include "Glass.h"

void Glass::init()
{
}

void Glass::update(float deltaTime)
{
	if (isAnySpot) {
		switch (spotPower)
		{
		case 1:
			currentFrame = spotAnim.getKeyFrameIndexBased(2);
			break;
		case 2:
			currentFrame = spotAnim.getKeyFrameIndexBased(1);
			break;
		case 3:
			currentFrame = spotAnim.getKeyFrameIndexBased(0);
			break;
		case 0:
			isAnySpot = false;
		default:
			isAnySpot = false;
			break;
		}
	}
}

void Glass::draw(SpriteBatch * batch)
{
	Object_Sprite.draw(*batch);
	vec4 uvrect;
	if(isAnySpot){
		uvrect = vec4(currentFrame.kf_u, currentFrame.kf_v, currentFrame.kf_u2, currentFrame.kf_v2);
		spot.draw(*batch, uvrect, currentFrame.kf_width, currentFrame.kf_height);
	}
}
