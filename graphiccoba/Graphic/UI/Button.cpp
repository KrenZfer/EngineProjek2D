#include "Button.h"


EngineProject2D::Button::Button(string _TAG) {
	TAG = _TAG;
	isActive = true;
}

EngineProject2D::Button::~Button() {

}

void EngineProject2D::Button::init(float x, float y, float scale, const char* texturefilePath, float depth){
	this->posx = x;
	this->posy = y;
	this->s_texture = texturefilePath;
	this->btn_scale = scale;

	btn_sprite.init(posx, posy, btn_scale, s_texture, depth);

	this->ButtonWidth = btn_sprite.getTexture().width;
	this->ButtonHeight = btn_sprite.getTexture().height;
	//cout << "buttonSize: " << ButtonWidth << ", " << ButtonHeight << endl;
}

void EngineProject2D::Button::init(float x, float y, float scale, const char * texturefilePath, float depth, InputManager * inputManager, Camera *camera, vec2 screenSize)
{
	init(x, y, scale, texturefilePath, depth);
	Binput = inputManager;
	btn_Camera = camera;
	btn_screenSize = screenSize;
	//cout << "ScreenSize : " << btn_screenSize.x << ", " << btn_screenSize.y << endl;
}

void EngineProject2D::Button::draw(SpriteBatch &batch){
	btn_sprite.draw(batch);
}

void EngineProject2D::Button::draw(SpriteBatch & batch, vec4 uvrect, float width, float height)
{
	ButtonWidth = width;
	ButtonHeight = height;
	btn_sprite.draw(batch, uvrect, width, height);
}

bool EngineProject2D::Button::onClicked()
{
	if (Binput->isKeyPressed(SDL_BUTTON_LEFT) && isActive)
	{
		return onHover();
	}
	return false;
}

bool EngineProject2D::Button::onHover()
{
	if ((mouseX > cCoordXY.x) && (mouseX < cCoordHW.x) && (mouseY > cCoordXY.y) && (mouseY < cCoordHW.y) && isActive)
	{
		//cout << "Nama Button : " << TAG << endl;
		//cout << "coord button XY : " << cCoordXY.x << ", " << cCoordXY.y << endl;
		//cout << "coord button HW : " << cCoordHW.x << ", " << cCoordHW.y << endl;
		//cout << "mouse : " << mouseX << ", " << mouseY << endl;
		return true;
	}
	else {
		return false;
	}
}

int EngineProject2D::Button::convertMouseY(int mouseY)
{
	float temp;
	float screenHeight = btn_screenSize.y;
	float cMouseY = mouseY;
	if (mouseY>screenHeight/2)
	{
		temp = mouseY - (screenHeight/2);
		cMouseY = (screenHeight / 2) - temp;
	}
	else if(mouseY < screenHeight/2)
	{
		temp = (screenHeight / 2) - mouseY;
		cMouseY = (screenHeight / 2) + temp;
	}
	return cMouseY;
}

void EngineProject2D::Button::update() {
	SDL_GetMouseState(&mouseX,&mouseY);
	cCoordXY = btn_Camera->convertWorldCoordstoScreenCoords(vec2(posx, posy));
	cCoordHW = vec2(ButtonWidth + cCoordXY.x, ButtonHeight + cCoordXY.y);
	mouseY = convertMouseY(mouseY);
}