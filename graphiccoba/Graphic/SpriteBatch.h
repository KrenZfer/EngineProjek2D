#ifndef _H_SPRITE_BATCH_H_
#define _H_SPRITE_BATCH_H_

#include <GLM\glm.hpp>
#include <GL\glew.h>
#include <vector>
#include "Vertex.h"

using namespace glm;
using namespace std;

namespace EngineProject2D {

	enum class GlyphSortType {NONE, FRONT_TO_BACK, BACK_TO_FRONT, TEXTURE};

	class Glyph {

	public:
		Glyph(){}
		Glyph(const vec4& destRect, const vec4& uvRect, GLuint Texture, float depth, const RGBA8 color);
		Glyph(const vec4& destRect, const vec4& uvRect, GLuint Texture, float depth, const RGBA8 color, float angle);
		GLuint texture;
		float depth;
		Vertex topleft;
		Vertex topright;
		Vertex bottomleft;
		Vertex bottomright;

	private:
		vec2 rotatePoint(vec2 position, float angle);
	};

	class RenderBatch {
	public:
		RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset), numVertices(NumVertices), texture(Texture) {}
		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};

	class SpriteBatch {

	public:
		SpriteBatch();
		~SpriteBatch();
		void Init();
		void begin(GlyphSortType glyph = GlyphSortType::TEXTURE);
		void end();

		void draw(const vec4& destRec, const vec4& uvRect, GLuint texture, float depth, RGBA8& color);
		void draw(const vec4& destRec, const vec4& uvRect, GLuint texture, float depth, RGBA8& color, float angle);
		void draw(const vec4& destRec, const vec4& uvRect, GLuint texture, float depth, RGBA8& color, const vec2& dir);
		void renderBatch();

		/*
		set VAO, if set to 0, it will automatically generate
		*/
		void setVAO(GLuint vao);
		/*
		set VBO, if set to 0, it will automatically generate
		*/
		void setVBO(GLuint vbo);

		void beginCreateVertexBuffer();
		void endCreateVertexBuffer();
		void setVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

	private:
		void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();

		static bool compareFronttoBack(Glyph* a, Glyph* b);
		static bool compareBacktoFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		GlyphSortType glyphSortType;
		GLuint s_vao;
		GLuint s_vbo;
		vector<Glyph*> s_glyphPointer;
		vector<Glyph>  s_glyphs;
		vector<RenderBatch> s_renderBatchs;
	};

}

#endif // !_H_SPRITE_BATCH_H_

