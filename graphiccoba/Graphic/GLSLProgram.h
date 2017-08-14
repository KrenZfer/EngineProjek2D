#ifndef _H_GLSL_PROGRAM_H_
#define _H_GLSL_PROGRAM_H_

#include <GL\glew.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace EngineProject2D {

	class GLSLProgram {
		GLuint program;
	public:
		GLuint BuildShader(const char* svertexpath, const char* sfragmentpath, const char* sgeometrypath = nullptr);
		GLuint getUniformLocation(const char* var);
		void useShader();
		void unuseShader();
	private:
		void checkShaderError(GLuint shader, string type);


	};

}


#endif // !_H_GLSL_PROGRAM_H_

