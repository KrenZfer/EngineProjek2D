#ifndef _H_PERSON_H_
#define _H_PERSON_H_

#include <Graphic\Sprite.h>
#include <Graphic\SpriteBatch.h>
#include <Graphic\GLSLProgram.h>
#include <Graphic\Camera.h>
#include <Core\InputManager.h>
#include <SDL\SDL.h>

using namespace EngineProject2D;

class Person {

public:
	Person();
	Person(vec2 Position, float scale, Camera camera, InputManager *inputManager);
	~Person();

	void init();
	void update(Camera camera, float deltaTime);
	void draw();

private:

	void initShader();

	const char* s_texturePath;
	GLSLProgram s_Program;
	Sprite s_human;
	SpriteBatch s_humanBatch;
	Camera s_camera;
	vec2 s_position;
	float s_scale;
	InputManager *s_input;

};


#endif // !_H_PERSON_H_

