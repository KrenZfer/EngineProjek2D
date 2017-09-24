#include "Person.h"
#include  <GLM\gtc\type_ptr.hpp>

Person::Person(vec2 position, const char* pathTexture, float scale, bool flip, Camera *camera, InputManager *inputManager) :
	GameObject(Sprite("PLAYER"))
{
	s_position = position;
	s_texturePath = pathTexture;
	s_scale = scale;
	s_camera = camera;
	s_input = inputManager;
	action = false;
	ulang = false;
}

Person::~Person()
{
}

void Person::init()
{
	Object_Sprite.init(s_position.x, s_position.y, s_scale, s_texturePath, 7.0f);
	playerAction = Animation("WalkingAlien");
	playerAction.createKeyFrame(Object_Sprite, 1, 2);
	key = playerAction.getCurrentKeyFrame(0.0f);
}


void Person::update(float deltaTime)
{
	Object_Sprite.setPosition(s_position);
	checkInput(deltaTime);
	if (action || ulang) {
		key = playerAction.getCurrentKeyFrame(deltaTime);
	}
	counterrepeat += deltaTime;
	if (counterrepeat > 200) {
		ulang = false;
	}
}

void Person::draw(SpriteBatch *batch)

{
	/*
		Sebeneranya animasi itu bisa menghandle 1 jenis animasi contoh berjalan / idle / attack
		apakah seperti itu????
	*/

	vec4 uvrect = vec4(key.kf_u, key.kf_v, key.kf_u2, key.kf_v2);
	//draw everything
	Object_Sprite.draw(*batch, uvrect, key.kf_width, key.kf_height);
	/*cout << "Player size : " << this->key.kf_width << ", " << key.kf_height << endl;*/
}

void Person::initShader()
{
	s_Program.BuildShader("Shaders/spriteShader.vert", "Shaders/spriteShader.frag");
}

