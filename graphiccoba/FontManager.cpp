#include "FontManager.h"
#include "ErrorHandling.h"

EngineProject2D::FontManager::FontManager()
{
}

EngineProject2D::FontManager::~FontManager()
{
}

void EngineProject2D::FontManager::InitFont(int fontsize, const char * fontname)
{
	this->fontSize = fontsize;
	this->fontName = fontname;
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		ErrorHandling::fatalError("Could not initialize FreeType Library");
	}
	FT_Face face;
	if (FT_New_Face(ft, fontName, 0, &face)) {
		ErrorHandling::fatalError("Failed to load Font : "+ *fontName);
	}

	FT_Set_Pixel_Sizes(face, 0, fontSize);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (GLubyte c = 0; c < 128; c++) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			ErrorHandling::fatalError("Unable to load this glyph");
			continue;
		}

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D
			, 0
			, GL_RED
			, face->glyph->bitmap.width
			, face->glyph->bitmap.rows
			, 0
			, GL_RED
			, GL_UNSIGNED_BYTE
			, face->glyph->bitmap.buffer
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		Character chara = {
			texture,
			ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(GLuint)face->glyph->advance.x
		};

		characters.insert(pair<GLchar, Character>(c, chara));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

vec2 EngineProject2D::FontManager::measure(string s)
{
	vec2 size(0, 0);
	string::const_iterator c;
	int sx = 0;
	for (c = s.begin(); c != s.end(); c++) {
		Character ch = characters[*c];
		if (size.y < ch.size.y) {
			size.y = ch.size.y;
		}
		sx += ch.Advanced - ch.Bearing.x;
	}
	size.x = sx;
	return size;
}

void EngineProject2D::FontManager::draw(SpriteBatch & batch, string text, vec2 position, vec2 scale, RGBA8 color, float depth, Justification justify)
{
	vec2 pos = position;
	if (justify == Justification::CENTER) {
		position.x -= measure(text).x * scale.x / 2;
	}
	if (justify == Justification::CENTER) {
		position.x -= measure(text).x * scale.x;
	}

	string::const_iterator cs;
	for (cs = text.begin(); cs != text.end(); cs++) {
		Character ch = characters[*cs];
		GLfloat xpos = position.x + ch.Bearing.x * scale.x;
		GLfloat ypos = position.y - (ch.size.y - ch.Bearing.y) * scale.y;
		GLfloat w = ch.size.x * scale.x;
		GLfloat h = ch.size.y * scale.y;
		vec4 _destRec(xpos, ypos, w, h);
		vec4 _uvRect(1, 1, 0, 0);
		batch.draw(_destRec, _uvRect, ch.TextureID, depth, color);
		position.x += (ch.Advanced >> 6) * scale.x;
	}
}

