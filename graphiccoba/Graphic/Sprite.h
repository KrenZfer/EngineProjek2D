#ifndef _H_SPRITE_H_
#define _H_SPRITE_H_

#include "ImageTexture.h"
#include <GL\glew.h>
#include <string>
#include "ResourceManager.h"
#include "Vertex.h"
#include "SpriteBatch.h"

using namespace std;

namespace EngineProject2D {

	class Sprite {

	public:
		Sprite();
		Sprite(string TAG);
		~Sprite();

		void init(vec2 position, vec2 scale, const char* texturefilePath, float depth = 0.0f, RGBA8 tint = RGBA8(255, 255, 255, 255));
		void init(float x, float y, float scale, const char* texturefilePath, float depth = 0.0f, RGBA8 tint = RGBA8(255, 255, 255, 255));
		void update();
		void draw(SpriteBatch &batch);
		void draw(SpriteBatch &batch, vec4 uvrect, float width, float height);

		void setPosition(vec2 position);
		void setScale(float scale);
		void setScale(vec2 scale);
		void setColor(RGBA8 tint);
		void setSize(float width, float height);
		void setSize(vec2 size);

		vec2 getPosition() { return s_position; }
		vec2 getScale() { return s_scale; }
		vec2 getSize() { return vec2(s_width, s_height); }


		ImageTexture getTexture() { return s_texture; }

	private:
		vec2 s_position;
		vec2 s_scale;
		float s_width;
		float s_height;
		float s_depth;
		GLuint s_vboID;
		ImageTexture s_texture;
		RGBA8 s_color;
		string SPRITE_TAG;

		vec4 destRect;
		vec4 uvRect;

	};

}

#endif // !_H_SPRITE_H_


