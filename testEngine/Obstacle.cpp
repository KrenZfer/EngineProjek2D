#include "Obstacle.h"

Obstacle::Obstacle(vec2 position, OBSTACLE_TYPE type) : GameObject(Sprite("OBSTACLE"), "OBSTACLE")
{
	obs_type = type;
	obs_position = position;
	texturePath = "Texture/obstacle1.png";
	switch (type)
	{
	case Obstacle::COMPUTER:
		destruct_power = 1;
		obs_speed = 1.5f * BASE_SPEED;
		row = 2;
		col = 5;
		texturePath = "Texture/obstacle1.png";
		obstAnim = Animation("Computer");
		break;
	case Obstacle::COUCH:
		destruct_power = 2;
		obs_speed = 2.0f * BASE_SPEED;
		row = 1;
		col = 3;
		texturePath = "Texture/obstacle2.png";
		obstAnim = Animation("Couch");
		break;
	case Obstacle::CLOSET:
		destruct_power = 3;
		obs_speed = 2.5f * BASE_SPEED;
		row = 1;
		col = 1;
		texturePath = "Texture/obstacle3.png";
		obstAnim = Animation("Closet");
		break;
	default:
		break;
	}
	init();
}

Obstacle::~Obstacle()
{

}

void Obstacle::init()
{
	Object_Sprite.init(obs_position, vec2(1.0f), texturePath, 6.0f);
	obstAnim.createKeyFrame(Object_Sprite, row, col);
}

void Obstacle::draw(SpriteBatch * batch)
{
	Object_Sprite.draw(*batch, vec4(curKeyFrame.kf_u, curKeyFrame.kf_v, curKeyFrame.kf_u2, curKeyFrame.kf_v2), curKeyFrame.kf_width, curKeyFrame.kf_height);
}

void Obstacle::update(float deltaTime)
{
	Object_Sprite.setPosition(obs_position);
	curKeyFrame = obstAnim.getCurrentKeyFrame(deltaTime);
	freeFalling(deltaTime);
}