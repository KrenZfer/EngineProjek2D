#include "ImageLoader.h"

namespace EngineProject2D {

	ImageTexture EngineProject2D::ImageLoader::imageLoad(const char* imagePath)
	{
		ImageTexture texture = {};
		int width, height;

		glGenTextures(1, &(texture.GLid));
		glBindTexture(GL_TEXTURE_2D, texture.GLid);

		unsigned char* image = SOIL_load_image(imagePath, &width, &height, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		texture.width = width;
		texture.height = height;
		
		return texture;
	}

}
