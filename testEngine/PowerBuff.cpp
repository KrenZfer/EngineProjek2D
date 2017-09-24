#include "PowerBuff.h"
#include "Player.h"


// time on mili-second
PowerBuff::PowerBuff(POWER_UP power, vec2 position) : GameObject(Sprite("POWER"), "POWER")
{
	hasActivated = false;
	switch (power)
	{
	case POWER_UP::BURGER:
		pb_status = "HEAL";
		pb_time = 0;
		pb_speed = 0.3f;
		texturePath = "Texture/healbuff.png";
		buffAnim = Animation("BURGER");
		animcol = 1;
		animrow = 1;
		break;
	case POWER_UP::SODA:
		pb_status = "SPEED-UP";
		pb_time = 2000;
		pb_speed = 0.3f;
		texturePath = "Texture/speedupbuff.png";
		buffAnim = Animation("SODA");
		animcol = 1;
		animrow = 1;
		break;
	default:
		break;
	}
	pb_position = position;
	init();
}

PowerBuff::PowerBuff(POWER_DOWN power, vec2 position) : GameObject(Sprite("POWER"), "POWER")
{
	hasActivated = false;
	switch (power)
	{
	case PowerBuff::ICE_CUBE:
		pb_status = "FREEZE";
		pb_time = 2000;
		pb_speed = 0.3f;
		texturePath = "Texture/freezebuff.png";
		buffAnim = Animation("ICE_CUBE");
		animcol = 4;
		animrow = 1;
		break;
	case PowerBuff::BEER:
		pb_status = "DRUNK";
		pb_time = 2000;
		pb_speed = 0.3f;
		texturePath = "Texture/drunkbuff.png";
		buffAnim = Animation("BEER");
		animcol = 1;
		animrow = 1;
		break;
	default:
		break;
	}
	pb_position = position;
	init();
}

PowerBuff::~PowerBuff()
{
}

void PowerBuff::init()
{
	Object_Sprite.init(pb_position, vec2(1.0f), texturePath, 6.0f);
	buffAnim.createKeyFrame(Object_Sprite, animrow, animcol);
}

void PowerBuff::update(float deltaTime)
{
	Object_Sprite.setPosition(pb_position);
 	currentKey = buffAnim.getCurrentKeyFrame(deltaTime);
	freeFalling(deltaTime);
	//cout << "Power buff pos : " << pb_position.x << ", " << pb_position.y << endl;
}

void PowerBuff::activateBuff(Player *player)
{
	if (pb_status == "HEAL") {
		player->playerHeal();
	}else if (pb_status == "SPEED-UP") {
		player->playerSpeedUp(pb_time);
	}else if (pb_status == "FREEZE") {
		player->playerFreeze(pb_time);
	}else if (pb_status == "DRUNK") {
		player->playerDrunk(pb_time);
	}
	hasActivated = true;
}

void PowerBuff::draw(SpriteBatch * batch)
{
	Object_Sprite.draw(*batch, vec4(currentKey.kf_u, currentKey.kf_v, currentKey.kf_u2, currentKey.kf_v2), currentKey.kf_width, currentKey.kf_height);
}
