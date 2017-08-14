#include "ImageLoader.h"
#include "ErrorHandling.h"

namespace EngineProject2D {

	ImageTexture EngineProject2D::ImageLoader::imageLoad(const char* imagePath)
	{
		ImageTexture texture = {};
		int width, height;
		GLuint texs;
		glGenTextures(1, &texs);
		glBindTexture(GL_TEXTURE_2D, texs);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);

		unsigned char* image = SOIL_load_image(imagePath, &width, &height, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

		if (image == nullptr) {
			ErrorHandling::fatalError("ERROR::IMAGE NOT FOUND");
		}

		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);

		texture.GLid = texs;
		texture.width = width;
		texture.height = height;
		
		return texture;
	}

}
