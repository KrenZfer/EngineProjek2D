#ifndef _H_BUTTON_H_
#define _H_BUTTON_H_

#include <SDL\SDL.h>
#include <GLM\glm.hpp>
#include "../WindowManager.h"
#include "../../Core/InputManager.h"
#include "../../Core/GameCore.h"
#include "../Sprite.h"
#include "../SpriteBatch.h"
#include "../Camera.h"

using namespace glm;
namespace EngineProject2D{
	class Button {
	public:
		Button(string _TAG = "BUTTON");
		~Button();
		void init(float x, float y, float scale, const char* texturefilePath, float depth, InputManager *inputManager, Camera *camera, vec2 screenSize);
		void update();
		void draw(SpriteBatch &batch);
		void draw(SpriteBatch &batch, vec4 uvrect, float width, float height);

		bool onClicked();
		bool onHover();

		void setPosition(vec2 position) { 
			posx = position.x;
			posy = position.y;
			btn_sprite.setPosition(vec2(posx,posy)); 
		}
		Sprite getSprite() { return btn_sprite; }

		void setButtonActive(bool active) { isActive = active; }
		bool isButtonActive() { return isActive; }

	private:

		void init(float x, float y, float scale, const char* texturefilePath, float depth);
		int convertMouseY(int mouseY);

		string TAG;
		InputManager* Binput;
		Camera *btn_Camera;
		bool isActive;
		vec2 btn_screenSize;
		int mouseX, mouseY;
		Sprite btn_sprite;
		vec2 cCoordXY, cCoordHW;
		float posx, posy;
		float ButtonWidth;
		float ButtonHeight;
		const char* s_texture;
		float btn_scale;
	};
}
#endif // !_H_BUTTON_H_