#include "FontManager.h"
#include "ErrorHandling.h"
#include <algorithm>

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

	//mencari nilai dari lebar dan tinggi atlas yang pas dengan family font yang diinginkan
	int x = 0, y = 0, w = 0, h = 0;
	for (GLubyte c = 32; c < 128; c++) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			ErrorHandling::fatalError("Unable to load this glyph");
			continue;
		}

		//bagaimana memberikan texture cooridnat pada tiap character tulisan dengan benar
		if (x + face->glyph->bitmap.width + 1 >= MAXWIDTH) {
			w = std::max(w, x);
			h += y;
			x = 0;
			y = 0;
		}		

		x += face->glyph->bitmap.width + 1;

		y = std::max(y, face->glyph->bitmap.rows);

		Character chara = {
			ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(GLuint)face->glyph->advance.x >> 6,
			vec4(),
			face->glyph->bitmap.buffer
		};

		characters.insert(pair<GLchar, Character>(c, chara));
	}

	fontAtlasWidth = std::max(w, x);
	fontAtlasHeight = h + y;

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	//glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &FontTexture);
	glBindTexture(GL_TEXTURE_2D, FontTexture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, fontAtlasWidth, fontAtlasHeight, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	map<GLchar, Character>::iterator chars;
	int offsetx = 0, offsety = 0;
	h = 0;

	for (chars = characters.begin(); chars != characters.end(); chars++) {

		if (offsetx + chars->second.size.x + 1 >= MAXWIDTH) {
			offsety += h;
			h = 0;
			offsetx = 0;
		}

		chars->second.txcoord.x = offsetx / fontAtlasWidth;
		chars->second.txcoord.y = offsety / fontAtlasHeight;
		chars->second.txcoord.z = chars->second.size.x / fontAtlasWidth;
		chars->second.txcoord.w = chars->second.size.y / fontAtlasHeight;

		Character ch = chars->second;
		glTexSubImage2D(GL_TEXTURE_2D, 0, offsetx, offsety, ch.size.x, ch.size.y, GL_RED, GL_UNSIGNED_BYTE, ch.pixels);

		h = std::max(h, static_cast<int>(chars->second.size.y));
		offsetx += chars->second.size.x + 1;
	}

	glBindTexture(GL_TEXTURE_2D, 0);

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

	/*glBindTexture(GL_TEXTURE_2D, texture);*/
	vec2 pos = position;
	if (justify == Justification::CENTER) {
		position.x += measure(text).x * scale.x / 2;
	}
	if (justify == Justification::RIGHT) {
		position.x += measure(text).x * scale.x;
	}

	string::const_iterator cs;
	for (cs = text.begin(); cs != text.end(); cs++) {
		Character ch = characters[*cs];
		GLfloat xpos = position.x + ch.Bearing.x * scale.x;
		GLfloat ypos = position.y - (ch.size.y - ch.Bearing.y) * scale.y;
		GLfloat w = ch.size.x * scale.x;
		GLfloat h = ch.size.y * scale.y;
		vec4 _destRec(xpos, ypos, w, h);
		batch.draw(_destRec, ch.txcoord, FontTexture, depth, color);
		position.x += ch.Advanced * scale.x;
	}
	//glBindTexture(GL_TEXTURE_2D, 0);
}


