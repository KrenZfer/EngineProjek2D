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

		void init(float x, float y, float scale, const char* texturefilePath, float depth = 0.0f, RGBA8 tint = RGBA8(255, 255, 255, 255));
		void draw();
		void draw(SpriteBatch &batch);

	private:
		float s_x;
		float s_y;
		float s_width;
		float s_height;
		float s_depth;
		GLuint s_vboID;
		ImageTexture s_texture;
		RGBA8 s_color;

	};

}

#endif // !_H_SPRITE_H_

