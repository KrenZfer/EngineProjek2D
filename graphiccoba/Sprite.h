#ifndef _H_SPRITE_H_
#define _H_SPRITE_H_

#include "ImageTexture.h"
#include <GL\glew.h>
#include <string>
#include "ResourceManager.h"
#include "Vertex.h"

using namespace std;

namespace EngineProject2D {

	class Sprite {

	public:
		Sprite();
		~Sprite();

		void init(int x, int y, float width, float height, const char* texturefilePath);
		void draw();

	private:
		int s_x;
		int s_y;
		float s_width;
		float s_height;
		GLuint s_vboID;
		ImageTexture s_texture;

	};

}

#endif // !_H_SPRITE_H_

