#include "SpriteBatch.h"
#include <algorithm>
#include <iostream>

namespace EngineProject2D {

	Glyph::Glyph(const vec4& destRect, const vec4& uvRect, GLuint Texture, float Depth, const RGBA8 color) : texture(Texture),  depth(Depth) {
		// x = 0, y = 1, z = 1, w = -1
		//0,0
		topleft.color = color;
		topleft.setPosition(destRect.x, destRect.y + destRect.w);
		topleft.setUV(uvRect.x, uvRect.y + uvRect.w);
		//0, 0

		//1,0
		topright.color = color;
		topright.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		topright.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
		//1,0

		//0,1
		bottomleft.color = color;
		bottomleft.setPosition(destRect.x, destRect.y);
		bottomleft.setUV(uvRect.x, uvRect.y);
		//0,1

		//1,1
		bottomright.color = color;
		bottomright.setPosition(destRect.x + destRect.z, destRect.y);
		bottomright.setUV(uvRect.x + uvRect.z, uvRect.y);
		//1,1
	}

	Glyph::Glyph(const vec4& destRect, const vec4& uvRect, GLuint Texture, float Depth, const RGBA8 color, float angle) : texture(Texture), depth(Depth) {
		glm::vec2 halfDimensions(destRect.z / 2.0f, destRect.w / 2.0f);

		glm::vec2 tl(-halfDimensions.x, halfDimensions.y);
		glm::vec2 bl(-halfDimensions.x, -halfDimensions.y);
		glm::vec2 br(halfDimensions.x, -halfDimensions.y);
		glm::vec2 tr(halfDimensions.x, halfDimensions.y);

		tl = rotatePoint(tl, angle) + halfDimensions;
		bl = rotatePoint(bl, angle) + halfDimensions;
		br = rotatePoint(br, angle) + halfDimensions;
		tr = rotatePoint(tr, angle) + halfDimensions;

		topleft.color = color;
		topleft.setPosition(destRect.x + tl.x, destRect.y + tl.y); //
		topleft.setUV(uvRect.x, uvRect.y + uvRect.w);

		bottomleft.color = color;
		bottomleft.setPosition(destRect.x + bl.x, destRect.y + bl.y); //
		bottomleft.setUV(uvRect.x, uvRect.y);

		topright.color = color;
		topright.setPosition(destRect.x + tr.x, destRect.y + tr.y); //
		topright.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		bottomright.color = color;
		bottomright.setPosition(destRect.x + br.x, destRect.y + br.y); //
		bottomright.setUV(uvRect.x + uvRect.z, uvRect.y);
	}

	vec2 Glyph::rotatePoint(vec2 position, float angle) {
		vec2 vectorTemp;
		vectorTemp.x = position.x * cos(angle) - position.y * sin(angle);
		vectorTemp.y = position.x * sin(angle) + position.y * cos(angle);
		return vectorTemp;
	}

	SpriteBatch::SpriteBatch() : s_vao(0), s_vbo(0){

	}

	SpriteBatch::~SpriteBatch()
	{

	}

	void SpriteBatch::Init()
	{
		createVertexArray();
	}

	void SpriteBatch::begin(GlyphSortType glyphsorttype)
	{
		glyphSortType = glyphsorttype;
		s_renderBatchs.clear();
		s_glyphs.clear();
	}

	void SpriteBatch::end()
	{
		s_glyphPointer.resize(s_glyphs.size());
		for (int i = 0; i < (int)s_glyphPointer.size(); i++) {
			s_glyphPointer[i] = &s_glyphs[i];
		}
		sortGlyphs();
		createRenderBatches();
	}

	void SpriteBatch::draw(const vec4 & destRec, const vec4 & uvRect, GLuint texture, float depth, RGBA8 & color)
	{
		s_glyphs.emplace_back(destRec, uvRect, texture, depth, color);
	}

	void SpriteBatch::draw(const vec4 & destRec, const vec4 & uvRect, GLuint texture, float depth, RGBA8 & color, float angle)
	{
		s_glyphs.emplace_back(destRec, uvRect, texture, depth, color, angle);
	}

	void SpriteBatch::draw(const vec4 & destRec, const vec4 & uvRect, GLuint texture, float depth, RGBA8 & color, const vec2 & dir)
	{
		const vec2 right(1.0f, 0.0f);
		float angle = acos(dot(right, dir));
		if (dir.y < 0.0f) angle = -angle;
		s_glyphs.emplace_back(destRec, uvRect, texture, depth, color, angle);
	}

	void SpriteBatch::renderBatch()
	{
		glBindVertexArray(s_vao);
		for (int i = 0; i < (int)s_renderBatchs.size(); i++) {
			glBindTexture(GL_TEXTURE_2D, s_renderBatchs[i].texture);
			
			glDrawArrays(GL_TRIANGLES, s_renderBatchs[i].offset, s_renderBatchs[i].numVertices);
		}

		glBindVertexArray(0);
	}

	void SpriteBatch::setVAO(GLuint vao)
	{
		if (vao == 0) {
			glGenVertexArrays(1, &s_vao);
		}
		else {
			s_vao = vao;
		}
	}

	void SpriteBatch::setVBO(GLuint vbo)
	{
		if (vbo == 0) {
			glGenBuffers(1, &s_vbo);
		}
		else {
			s_vbo = vbo;
		}
	}

	void SpriteBatch::beginCreateVertexBuffer()
	{
		if (s_vao == 0)
		{
			glGenVertexArrays(1, &s_vao);
		}

		if (s_vbo == 0)
		{
			glGenBuffers(1, &s_vbo);
		}

		glBindVertexArray(s_vao);
		glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
	}

	void SpriteBatch::endCreateVertexBuffer()
	{
		glBindVertexArray(0);
	}

	void SpriteBatch::setVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	}

	void SpriteBatch::createRenderBatches()
	{
		vector<Vertex> vertices;
		vertices.resize(s_glyphPointer.size() * 6);

		if (s_glyphPointer.empty()) {
			return;
		}

		int currentVertex = 0;
		int offset = 0;
		s_renderBatchs.emplace_back(offset, 6, s_glyphPointer[0]->texture);
		vertices[currentVertex++] = s_glyphPointer[0]->topleft;
		vertices[currentVertex++] = s_glyphPointer[0]->bottomleft;
		vertices[currentVertex++] = s_glyphPointer[0]->bottomright;
		vertices[currentVertex++] = s_glyphPointer[0]->bottomright;
		vertices[currentVertex++] = s_glyphPointer[0]->topright;
		vertices[currentVertex++] = s_glyphPointer[0]->topleft;
		offset += 6; //Used to keep track of which vertices to render in the batch. Ie. we use the same texture but all the vertices are different so we should be able to pickout the correct ones to render.

		for (int currentGlyph = 1; currentGlyph < (int)s_glyphPointer.size(); currentGlyph++)
		{
			if (s_glyphPointer[currentGlyph]->texture != s_glyphPointer[currentGlyph - 1]->texture)
			{
				s_renderBatchs.emplace_back(offset, 6, s_glyphPointer[currentGlyph]->texture);
			}
			else
			{
				s_renderBatchs.back().numVertices += 6;
			}

			vertices[currentVertex++] = s_glyphPointer[currentGlyph]->topleft;
			vertices[currentVertex++] = s_glyphPointer[currentGlyph]->bottomleft;
			vertices[currentVertex++] = s_glyphPointer[currentGlyph]->bottomright;
			vertices[currentVertex++] = s_glyphPointer[currentGlyph]->bottomright;
			vertices[currentVertex++] = s_glyphPointer[currentGlyph]->topright;
			vertices[currentVertex++] = s_glyphPointer[currentGlyph]->topleft;
			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
		//Orphan the buffer //Avoids having to overwrite data.
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//Upload new data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}



	void SpriteBatch::createVertexArray()
	{
		if (s_vao == 0)
		{
			glGenVertexArrays(1, &s_vao);
		}

		if (s_vbo == 0)
		{
			glGenBuffers(1, &s_vbo); 
		}

		glBindVertexArray(s_vao);
		glBindBuffer(GL_ARRAY_BUFFER, s_vbo);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		//Point opengl to the data
		//Position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		//Color attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		//UV attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}

	void SpriteBatch::sortGlyphs()
	{
		switch (glyphSortType) {
		case GlyphSortType::BACK_TO_FRONT:
			stable_sort(s_glyphPointer.begin(), s_glyphPointer.end(), compareBacktoFront); //Equal elements will retain the same order
			break;
		case GlyphSortType::FRONT_TO_BACK:
			stable_sort(s_glyphPointer.begin(), s_glyphPointer.end(), compareFronttoBack);
			break;
		case GlyphSortType::TEXTURE:
			stable_sort(s_glyphPointer.begin(), s_glyphPointer.end(), compareTexture);
			break;
		}
	}

	bool SpriteBatch::compareFronttoBack(Glyph * a, Glyph * b)
	{
		if (a->depth > b->depth)
			return true;
		else
			return false;
	}

	bool SpriteBatch::compareBacktoFront(Glyph * a, Glyph * b)
	{
		if (a->depth < b->depth)
			return true;
		else
			return false;
	}

	bool SpriteBatch::compareTexture(Glyph * a, Glyph * b)
	{
		if (a->texture > b->texture)
			return true;
		else
			return false;
	}

}