#include "Player.h"

Player::Player()
{
}

Player::Player(vec2 Position, float scale, Camera camera, InputManager * inputManager)
{
	s_position = Position;
	s_scale = scale;
	s_camera = camera;
	s_input = inputManager;
	s_speed = 0.1f;
	s_displacement = vec2(0.0f);
}

Player::~Player()
{
	Person::~Person();
}

void Player::checkInput(float deltaTime)
{
	//cout << "deltaTime : " << deltaTime << endl;
	if (s_input->isKeyDown(SDLK_d)) {
		prev_position = s_position;
		s_position.x += s_speed * deltaTime;
		walk = true;
		//cout << "displacement : " << s_speed * deltaTime << endl;
	}
	else if (s_input->isKeyDown(SDLK_a)) {
		prev_position = s_position;
		s_position.x -= (s_speed * deltaTime);
		walk = true;
	}
	else if (s_input->isKeyDown(SDLK_w)) {
		prev_position = s_position;
		s_position.y += s_speed * deltaTime;
		walk = true;
	}
	else if (s_input->isKeyDown(SDLK_s)) {
		prev_position = s_position;
		s_position.y -= (s_speed * deltaTime);
		walk = true;
	}
	else {
		walk = false;
	}

	if (s_input->isKeyDown(SDLK_q)) {
		s_human.setScale(0.000001f * deltaTime);
	}
	if (s_input->isKeyDown(SDLK_e)) {
		s_human.setScale(-0.000001f * deltaTime);
	}
}

void Player::checkUpdate(Sprite sprite)
{
	//coba buat mekanisme dimana terdapat sprite manager yang menyimpan semua data mengenai sprite
	// dan setiap sprite punya tag atau name yang dapat menjadi key dari spite tersebut untuk ditemukan
	//Person::update(camera, deltaTime);
	if (s_human.collides(sprite)) {
		s_position = prev_position;
	}
}

