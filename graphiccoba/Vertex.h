#ifndef _H_VERTEX_H_
#define _H_VERTEX_H_

#include <GL\glew.h>

namespace EngineProject2D {

	struct Position
	{
		float x;
		float y;
	};

	struct UV {
		float u;
		float v;
	};

	struct RGBA8 {
		RGBA8() : R(0), G(0), B(0), A(0){}
		RGBA8(GLubyte r, GLubyte g, GLubyte b, GLubyte a): R(r), G(g), B(b), A(a){}
		GLubyte R;
		GLubyte G;
		GLubyte B;
		GLubyte A;
	};

	struct Vertex {

		Position position;
		UV uv;
		RGBA8 color;

		void setPosition(float x, float y) {
			position.x = x;
			position.y = y;
		}

		void setUV(float u, float v) {
			uv.u = u;
			uv.v = v;
		}

		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
			color = RGBA8(r, g, b, a);
		}

	};

}

#endif // !_H_VERTEX_H_

