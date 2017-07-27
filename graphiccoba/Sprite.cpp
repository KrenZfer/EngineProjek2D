#include "Sprite.h"

EngineProject2D::Sprite::Sprite()
{
	s_vboID = 0;
}

EngineProject2D::Sprite::~Sprite()
{
	if (s_vboID != 0) {
		glDeleteBuffers(1, &s_vboID);
	}
}

void EngineProject2D::Sprite::init(int x, int y, float width, float height, const char* texturefilePath)
{
	s_x = x;
	s_y = y;
	s_width = width;
	s_height = height;

	if (s_vboID == 0) {
		glGenBuffers(1, &s_vboID);
	}

	s_texture = ResourceManager::getImageTexture(texturefilePath);

	Vertex vertex[6];
	// draw Rectangle from 2 Triangle
	// first Triangle
	vertex[0].setPosition(x + width, y + height);
	vertex[0].setUV(1.0f, 1.0f);

	vertex[1].setPosition(x, y + height);
	vertex[1].setUV(0.0f, 1.0f);

	vertex[2].setPosition(x, y);
	vertex[2].setUV(0.0f, 0.0f);

	// second triangle
	vertex[3].setPosition(x, y);
	vertex[3].setUV(0.0f, 0.0f);

	vertex[4].setPosition(x + width, y);
	vertex[4].setUV(1.0f, 0.0f);

	vertex[5].setPosition(x + width, y + height);
	vertex[5].setUV(1.0f, 1.0f);

	for (int i = 0; i < 6; i++) {
		vertex[i].setColor(255, 255, 255, 255);
	}

	glBindBuffer(GL_ARRAY_BUFFER, s_vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void EngineProject2D::Sprite::draw()
{
	glBindTexture(GL_TEXTURE_2D, s_texture.GLid);

	glBindBuffer(GL_ARRAY_BUFFER, s_vboID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(0, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
