#include "GLSLProgram.h"
namespace EngineProject2D {

	GLuint EngineProject2D::GLSLProgram::BuildShader(const char * svertexpath, const char * sfragmentpath, const char * sgeometrypath)
	{
		string vertextCode;
		string fragmentCode;
		string geometryCode;
		ifstream vshaderFile;
		ifstream fshaderFile;
		ifstream gshaderFile;

		vshaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		fshaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		gshaderFile.exceptions(ifstream::failbit | ifstream::badbit);

		try {
			vshaderFile.open(svertexpath);
			fshaderFile.open(sfragmentpath);
			stringstream vshaderStream, fshaderStream;
			//read file's buffer content into stream
			vshaderStream << vshaderFile.rdbuf();
			fshaderStream << fshaderFile.rdbuf();

			vshaderFile.close();
			fshaderFile.close();

			vertextCode = vshaderStream.str();
			fragmentCode = fshaderStream.str();

			if (sgeometrypath != nullptr) {
				gshaderFile.open(sgeometrypath);
				stringstream gshaderStream;
				gshaderStream << gshaderFile.rdbuf();
				gshaderFile.close();
				geometryCode = gshaderStream.str();
			}

		}
		catch (ifstream::failure e) {
			cout << "ERR::SHADER FILE::CANNOT LOADED" << endl;
		}

		const GLchar* vshaderCode = vertextCode.c_str();
		const GLchar* fshaderCode = fragmentCode.c_str();
		//compile shader
		GLuint vertex, fragment;
		GLint success;
		GLchar infolog[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vshaderCode, NULL);
		glCompileShader(vertex);
		checkShaderError(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fshaderCode, NULL);
		glCompileShader(fragment);
		checkShaderError(fragment, "FRAGMENT");

		GLuint geometry;

		if (sgeometrypath != nullptr) {
			const GLchar* gshaderCode = geometryCode.c_str();

			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry, 1, &gshaderCode, NULL);
			glCompileShader(geometry);
			checkShaderError(geometry, "GEOMETRY");
		}

		program = glCreateProgram();
		checkShaderError(program, "PROGRAM");
		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		if (sgeometrypath != nullptr)
			glAttachShader(program, geometry);
		glLinkProgram(program);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		if (sgeometrypath != nullptr)
			glDeleteShader(geometry);

		return program;
	}

	void EngineProject2D::GLSLProgram::useShader()
	{
		glUseProgram(program);
	}

	void GLSLProgram::unuseShader()
	{
		glUseProgram(0);
	}

	void EngineProject2D::GLSLProgram::checkShaderError(GLuint shader, string type)
	{
		GLint success;
		GLchar infolog[1024];
		if (type != "PROGRAM") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 1024, NULL, infolog);
				cout << "| ERROR::SHADER-COMPILATION-ERROR of type" << type << "|\n" << infolog << "|\n-------------" << endl;
			}
		}
		else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 1024, NULL, infolog);
				cout << "| ERROR::PROGRAM-LINKING-ERROR of type" << type << "|\n" << infolog << "|\n-------------" << endl;
			}
		}
	}

}
