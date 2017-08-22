#include "Person.h"
#include  <GLM\gtc\type_ptr.hpp>

Person::Person()
{
}

Person::Person(vec2 position, float scale, bool flip, Camera camera, InputManager *inputManager)
{
	s_position = position;
	s_scale = scale;
	s_camera = camera;
	s_input = inputManager;
	walk = false;
}

Person::~Person()
{
	//disable shader
	s_Program.unuseShader();
}

void Person::init(const char* pathTexture)
{
	s_texturePath = pathTexture;
	initShader();
	s_human.init(s_position.x, s_position.y, s_scale, s_texturePath);
	walksimpson = Animation("WalkingSimpson", 4, 6);
	walksimpson.createKeyFrame(s_human.getTexture());
	key = walksimpson.getCurrentKeyFrame(0.0f);
}

void Person::update(Camera camera, float deltaTime)
{
	s_camera = camera;
	checkInput(deltaTime);
	s_human.setPosition(s_position);
	if (walk) {
		key = walksimpson.getCurrentKeyFrame(deltaTime);
	}
}

void Person::draw(SpriteBatch *batch)
{
	/*
		Sebeneranya animasi itu bisa menghandle 1 jenis animasi contoh berjalan / idle / attack
		apakah seperti itu????
	*/
	//enable shader
	s_Program.useShader();

	//input projection
	GLint projloc = s_Program.getUniformLocation("projection");
	mat4 projection = s_camera.getCameraMatrix();
	glUniformMatrix4fv(projloc, 1, GL_FALSE, value_ptr(projection));

	//input sampler
	GLint samplerloc = s_Program.getUniformLocation("texture0");
	glUniform1i(samplerloc, 0);
	vec4 uvrect = vec4(key.kf_u, key.kf_v, key.kf_u2, key.kf_v2);
	//draw everything
	s_human.draw(*batch, uvrect, key.kf_width, key.kf_height);

}

void Person::initShader()
{
	s_Program.BuildShader("Shaders/spriteShader.vert", "Shaders/spriteShader.frag");
}

