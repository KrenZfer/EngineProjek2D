#ifndef _H_FONT_MANAGER_H_
#define _H_FONT_MANAGER_H_

#include <GL\glew.h>
#include <ft2build.h>
#include <freetype\freetype.h>
#include <map>
#include <GLM\glm.hpp>
#include <string>
#include "SpriteBatch.h"

using namespace std;
using namespace glm;

#define MAXWIDTH 1024

namespace EngineProject2D {

	enum Justification {LEFT, CENTER, RIGHT};

	class FontManager {

	public:

		FontManager();
		~FontManager();

		struct Character {
			ivec2 size;
			ivec2 Bearing;
			GLuint Advanced;
			//untuk uvrect harus diubah beberapa
			vec4 txcoord;
			const void* pixels;
		};

		void InitFont(int fontsize, const char* fontname);
		vec2 measure(string s);
		void draw(SpriteBatch& batch, string text, vec2 position, vec2 scale, RGBA8 color, float depth, Justification justify);

		int fontSize;
		const char* fontName;
		string Text;
		map<GLchar, Character> characters;

	private:
		GLuint VAO, VBO;
		GLuint FontTexture;
		GLint fontAtlasWidth;
		GLint fontAtlasHeight;
	};

}

#endif // !_H_FONT_MANAGER_H_

