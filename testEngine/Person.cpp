#include "Person.h"
#include  <GLM\gtc\type_ptr.hpp>

Person::Person()
{
}

Person::Person(vec2 position, float scale, Camera camera, InputManager *inputManager)
{
	s_position = position;
	s_scale = scale;
	s_camera = camera;
	s_input = inputManager;
}

Person::~Person()
{
}

void Person::init()
{
	s_texturePath = "Texture/CharacterLeft.png";
	initShader();
	s_humanBatch.Init();
	s_human.init(s_position.x, s_position.y, s_scale, s_texturePath);
}

void Person::update(Camera camera, float deltaTime)
{
	s_camera = camera;
}

void Person::draw()
{
	//enable shader
	s_Program.useShader();

	//input projection
	GLint projloc = s_Program.getUniformLocation("projection");
	mat4 projection = s_camera.getCameraMatrix();
	glUniformMatrix4fv(projloc, 1, GL_FALSE, value_ptr(projection));

	//input sampler
	GLint samplerloc = s_Program.getUniformLocation("texture0");
	glUniform1i(samplerloc, 0);

	//begin batch
	s_humanBatch.begin();

	//draw everything
	s_human.draw(s_humanBatch);

	//end batch
	s_humanBatch.end();

	//draw all in batch
	s_humanBatch.renderBatch();

	//disable shader
	s_Program.unuseShader();
}

void Person::initShader()
{
	s_Program.BuildShader("Shaders/spriteShader.vert", "Shaders/spriteShader.frag");
}

