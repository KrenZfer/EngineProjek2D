#include "Sprite.h"

EngineProject2D::Sprite::Sprite()
{
	s_vboID = 0;
}

EngineProject2D::Sprite::~Sprite()
{
	if (s_vboID != 0) {
		glDeleteBuffers(1, &s_vboID);
	}
}

void EngineProject2D::Sprite::init(float x, float y, float scale, const char* texturefilePath, float depth, RGBA8 tint)
{

	if (s_vboID == 0) {
		glGenBuffers(1, &s_vboID);
	}

	s_texture = ResourceManager::getImageTexture(texturefilePath);

	s_x = x;
	s_y = y;
	s_depth = depth;
	s_color = tint;
	s_width = static_cast<float>(s_texture.width) / scale;
	s_height = static_cast<float>(s_texture.height) / scale;
}

void EngineProject2D::Sprite::draw(SpriteBatch & batch)
{
	vec4 destRect = vec4(s_x, s_y, s_width, s_height);
	vec4 uvRect = vec4(0.0f,0.0f,1.0f,1.0f);
	batch.draw(destRect, uvRect, s_texture.GLid, s_depth, s_color);

}
