#ifndef _H_PERSON_H_
#define _H_PERSON_H_

#include <Graphic\Sprite.h>
#include <Graphic\SpriteBatch.h>
#include <Graphic\GLSLProgram.h>
#include <Graphic\Camera.h>
#include <Core\InputManager.h>
#include <SDL\SDL.h>
#include <Graphic\Animation.h>

using namespace EngineProject2D;

class Person {

public:
	Person();
	Person(vec2 Position, float scale, bool flip, Camera camera, InputManager *inputManager);
	~Person();

	void init(const char* pathTexture);
	void update(Camera camera, float deltaTime);
	void draw(SpriteBatch *batch);

	virtual void checkInput(float deltaTime){}
	Sprite s_human;

protected:

	void initShader();

	const char* s_texturePath;
	GLSLProgram s_Program;
	SpriteBatch s_humanBatch;
	Animation walksimpson;
	KeyFrame key;
	Camera s_camera;
	vec2 s_position;
	float s_scale;
	InputManager *s_input;
	float s_speed;
	bool walk;


};


#endif // !_H_PERSON_H_

