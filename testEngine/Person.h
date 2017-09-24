#ifndef _H_PERSON_H_
#define _H_PERSON_H_

#include <Graphic\Sprite.h>
#include <Graphic\SpriteBatch.h>
#include <Graphic\GLSLProgram.h>
#include <Graphic\Camera.h>
#include <Core\InputManager.h>
#include <SDL\SDL.h>
#include <Graphic\Animation.h>
#include <Graphic\GameObject.h>


using namespace EngineProject2D;

class Person : public GameObject {

public:
	Person(vec2 Position, const char* pathTexture, float scale, bool flip, Camera *camera, InputManager *inputManager);
	~Person();

	virtual void init() override;
	virtual void update(float deltaTime) override;
	virtual void draw(SpriteBatch *batch) override;

	virtual void checkInput(float deltaTime){}
	//Sprite s_human;

	vec2 getPosition() { return s_position; }
	KeyFrame getKey() { return key; }
	vec2 getCenter() {
		return vec2(s_position.x + Object_Sprite.getSize().x / 2, s_position.y + Object_Sprite.getSize().y / 2);
	}

protected:

	void initShader();

	const char* s_texturePath;
	GLSLProgram s_Program;
	SpriteBatch s_humanBatch;
	Animation playerAction;
	KeyFrame key;
	Camera *s_camera;
	vec2 s_position;
	vec2 tempc_position;
	float s_scale;
	InputManager *s_input;
	float s_speed;
	bool action;
	int counterrepeat;
	bool ulang;


};


#endif // !_H_PERSON_H_

