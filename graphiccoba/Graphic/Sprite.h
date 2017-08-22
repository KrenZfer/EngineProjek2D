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
		~Sprite();

		void init(vec2 position, vec2 scale, const char* texturefilePath, float depth = 0.0f, RGBA8 tint = RGBA8(255, 255, 255, 255));
		void init(float x, float y, float scale, const char* texturefilePath, float depth = 0.0f, RGBA8 tint = RGBA8(255, 255, 255, 255));
		void update();
		void draw(SpriteBatch &batch);
		void draw(SpriteBatch &batch, vec4 uvrect, float width, float height);

		bool collides(Sprite sprite);

		void setPosition(vec2 position);
		void setScale(float scale);
		void setScale(vec2 scale);
		void setColor(RGBA8 tint);

		ImageTexture getTexture() { return s_texture; }

	private:
		vec2 s_position;
		float s_width;
		float s_height;
		float s_depth;
		GLuint s_vboID;
		ImageTexture s_texture;
		RGBA8 s_color;

		vec4 destRect;
		vec4 uvRect;

	};

}

#endif // !_H_SPRITE_H_


