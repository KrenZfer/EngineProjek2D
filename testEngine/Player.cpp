#include "Player.h"


Player::Player(vec2 Position, const char* pathTexture, float Scale, Camera *camera, InputManager & inputManager) : Person(Position, pathTexture, Scale, false, camera, &inputManager)
{
	s_speed = 0.3f;
	player_HEALTH = 5;
	action = false;
	ulang = false;
	takeDamage = true;
	isDrunk = false;
	isFreeze = false;
	waitforWipe = false;
	gondolaMove = false;
	waitforgondolaSound = false;
	status = PLAYER_STATUS::ALIVE;
	drunkFactor = 1;
	wiperSound = ResourceManager::getAudioData("Audio/oggfile/wipeAwal.ogg", false);
	gondolaSound = ResourceManager::getAudioData("Audio/oggfile/gondolaAwal.ogg", false);
	powerDownSound = ResourceManager::getAudioData("Audio/oggfile/powerDown.ogg", false);
	powerUpSound = ResourceManager::getAudioData("Audio/oggfile/powerUp.ogg", false);
	obstacleHit = ResourceManager::getAudioData("Audio/oggfile/hit.ogg", false);

	gondolaSound.setVolume(0.5f);
}

Player::~Player()
{
	Person::~Person();
}

void Player::checkInput(float deltaTime)
{
	if (!(temp.x < boundary.x || temp.x > boundary.y || temp.y < boundary.z || temp.y > boundary.w)) {
		s_position = temp;
	}
	
	colliderWiper.setPosition(
		vec2(Object_Sprite.getPosition().x + (Object_Sprite.getSize().x / 2.0f), Object_Sprite.getPosition().y + (Object_Sprite.getSize().y * 19.0f / 20.0f))
	);
	colliderWiper.setSize(
		vec2((Object_Sprite.getSize().x) / 2, (Object_Sprite.getSize().y) * 2 / 20.0f)
	);
	bodyCollider.setPosition(
		vec2(Object_Sprite.getPosition().x, Object_Sprite.getPosition().y + (Object_Sprite.getSize().y * 6.0f / 10.0f))
	);
	bodyCollider.setSize(
		vec2((Object_Sprite.getSize().x), (Object_Sprite.getSize().y) * 2.0f / 10.0f)
	);

	temp = s_position;

	if (!isFreeze) {
		
		if (s_input->isKeyDown(SDLK_d)) {
			temp.x += s_speed * deltaTime * drunkFactor;
			gondolaMove = true;
			action = false;
		}
		else if (s_input->isKeyDown(SDLK_a)) {
			temp.x -= (s_speed * deltaTime) * drunkFactor;
			gondolaMove = true;
			action = false;
		}
		else if (s_input->isKeyDown(SDLK_w)) {
			temp.y += s_speed * deltaTime * drunkFactor;
			gondolaMove = true;
			action = false;
		}
		else if (s_input->isKeyDown(SDLK_s)) {
			temp.y -= (s_speed * deltaTime) * drunkFactor;
			gondolaMove = true;
			action = false;
		}
		else if (s_input->isKeyDown(SDLK_SPACE)) {
			action = true;
			ulang = true;
			gondolaMove = false;
			counterrepeat = 0;
		}
		else {
			action = false;
			gondolaMove = false;
		}

		if (!waitforgondolaSound && gondolaMove) {
			gondolaSound.Play();
			waitforgondolaSound = true;
		}

		if (waitforgondolaSound && gondolaSound.getISound()->isFinished()) {
			waitforgondolaSound = false;
		}

		if (!gondolaMove) {
			waitforgondolaSound = false;
			gondolaSound.Stop();
		}

	}
	else {
		action = false;
		ulang  = false;
		gondolaMove = false;
	}

	if (ulang && !waitforWipe) {
		wiperSound.Play();
		waitforWipe = true;
	}

	if (waitforWipe && wiperSound.getISound()->isFinished()) {
		waitforWipe = false;
	}
}

void Player::checkUpdate(GameObject * object)
{
	if (
		bodyCollider.collidesWith(object)
		) {
		if (object->getTAG() == "OBSTACLE") {
			Obstacle *temp = (Obstacle*)object;
			tookObstacleDamage(temp);
			takeDamage = false;
			if (countInvcObs > INVINCIBLE) {
				takeDamage = true;
				countInvcObs = 0;
			}
		}
		if (object->getTAG() == "POWER") {
			PowerBuff *temp = (PowerBuff*)object;
			if (!temp->isActivated()) {
				temp->activateBuff(this);
			}
		}
	}
	if (colliderWiper.collidesWith(object)) {
		if (object->getTAG() == "GLASS") {
			Glass *temp = (Glass*)object;
			if (action) {
				temp->eraseSpot();
			}
		}
	}

	if (!takeDamage) {
		countInvcObs++;
	}

	//When Player Drunk
	if (drunkTime > 0) {
		drunkTime--;
	}
	else {
		isDrunk = false;
		drunkFactor = 1;
	}

	//When player frozed
	if (freezeTime > 0) {
		freezeTime--;
	}
	else {
		isFreeze = false;
	}

	//When player speed up
	if (speedUpTime > 0) {
		speedUpTime--;
	}
	else {
		s_speed = 0.3f;
	}
	if (player_HEALTH <= 0) {
		status = PLAYER_STATUS::DEAD;
	}
}

void Player::tookObstacleDamage(Obstacle * obs)
{
	if (takeDamage) {
		obstacleHit.Play();
		player_HEALTH -= obs->getDestructPower();
	}
}

void Player::playerHeal()
{
	powerUpSound.Play();
	if (player_HEALTH < 5) {
		player_HEALTH += 2;
	}
	if (player_HEALTH > 5) {
		player_HEALTH = 5;
	}
}

void Player::playerSpeedUp(int time)
{
	powerUpSound.Play();
	s_speed = 0.6f;
	speedUpTime = time;
}

void Player::playerDrunk(int time)
{
	powerDownSound.Play();
	isDrunk = true;
	drunkFactor = -1;
	drunkTime = time;
}

void Player::playerFreeze(int time)
{
	powerDownSound.Play();
	isFreeze = true;
	freezeTime = time;
}

