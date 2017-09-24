#include "Sprite.h"

EngineProject2D::Sprite::Sprite()
{
	s_vboID = 0;
	SPRITE_TAG = "OBJECT";
}

EngineProject2D::Sprite::Sprite(string TAG)
{
	s_vboID = 0;
	SPRITE_TAG = TAG;
}

EngineProject2D::Sprite::~Sprite()
{
	if (s_vboID != 0) {
		glDeleteBuffers(1, &s_vboID);
	}
}

void EngineProject2D::Sprite::init(vec2 position, vec2 scale, const char * texturefilePath, float depth, RGBA8 tint)
{
	if (s_vboID == 0) {
		glGenBuffers(1, &s_vboID);
	}

	s_texture = ResourceManager::getImageTexture(texturefilePath);

	s_position = position;
	s_scale = scale;
	s_depth = depth;
	s_color = tint;
	s_width = s_texture.width = s_texture.width * scale.x;
	s_height = s_texture.height = s_texture.height * scale.y;

	uvRect = vec4(0.0f, 0.0f, 1.0f, 1.0f);
}

void EngineProject2D::Sprite::init(float x, float y, float scale, const char* texturefilePath, float depth, RGBA8 tint)
{
	init(vec2(x, y), vec2(scale, scale), texturefilePath, depth, tint);
}

void EngineProject2D::Sprite::update()
{

}

void EngineProject2D::Sprite::draw(SpriteBatch & batch)
{
	destRect = vec4(s_position, s_width, s_height);
	batch.draw(destRect, uvRect, s_texture.GLid, s_depth, s_color);
}

void EngineProject2D::Sprite::draw(SpriteBatch & batch, vec4 uvrect, float width, float height)
{
	uvRect = uvrect;
	s_width = width;
	s_height = height;
	draw(batch);
}

void EngineProject2D::Sprite::setPosition(vec2 position)
{
	s_position = position;
}

void EngineProject2D::Sprite::setScale(float scale)
{
	s_width = s_width * scale;
	s_height = s_height * scale;
}

void EngineProject2D::Sprite::setScale(vec2 scale)
{
	s_width = s_width * scale.x;
	s_height = s_height * scale.y;
}

void EngineProject2D::Sprite::setColor(RGBA8 tint)
{
	s_color = tint;
}

void EngineProject2D::Sprite::setSize(float width, float height)
{
	s_width = width;
	s_height = height;
}

void EngineProject2D::Sprite::setSize(vec2 size)
{
	setSize(size.x, size.y);
}
