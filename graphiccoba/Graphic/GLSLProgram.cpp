#include "GLSLProgram.h"
namespace EngineProject2D {

	GLuint EngineProject2D::GLSLProgram::BuildShader(const char * svertexpath, const char * sfragmentpath, const char * sgeometrypath)
	{
		// 1. Retrieve the vertex/fragment source code from filePath
		string vertexCode;
		string fragmentCode;
		string geometryCode;
		ifstream vShaderFile;
		ifstream fShaderFile;
		ifstream gShaderFile;
		// ensures ifstream objects can throw exceptions:
		vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		gShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		try
		{
			// Open files
			vShaderFile.open(svertexpath);
			fShaderFile.open(sfragmentpath);
			stringstream vShaderStream, fShaderStream;
			// Read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// Convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
			//cout << "============== Shader Vertex =====================" << endl;
			//cout << vertexCode << endl;
			//cout << "============== Shader Fragment =====================" << endl;
			//cout << fragmentCode << endl;
			// If geometry shader path is present, also load a geometry shader
			if (sgeometrypath != nullptr)
			{
				gShaderFile.open(sgeometrypath);
				stringstream gShaderStream;
				gShaderStream << gShaderFile.rdbuf();
				gShaderFile.close();
				geometryCode = gShaderStream.str();
			}
		}
		catch (ifstream::failure e)
		{
			cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
		}
		const GLchar* vShaderCode = vertexCode.c_str();
		const GLchar * fShaderCode = fragmentCode.c_str();
		// 2. Compile shaders
		GLuint vertex, fragment;
		GLint success;
		GLchar infoLog[512];
		// Vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkShaderError(vertex, "VERTEX");
		// Fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkShaderError(fragment, "FRAGMENT");
		// If geometry shader is given, compile geometry shader
		GLuint geometry;
		if (sgeometrypath != nullptr)
		{
			const GLchar * gShaderCode = geometryCode.c_str();
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry, 1, &gShaderCode, NULL);
			glCompileShader(geometry);
			checkShaderError(geometry, "GEOMETRY");
		}
		// Shader Program
		program = glCreateProgram();
		glAttachShader(program, vertex);
		glAttachShader(program, fragment);
		if (sgeometrypath != nullptr)
			glAttachShader(program, geometry);
		glLinkProgram(program);
		checkShaderError(program, "PROGRAM");
		// Delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		if (sgeometrypath != nullptr)
			glDeleteShader(geometry);
		return program;
	}

	GLuint GLSLProgram::getUniformLocation(const char * var)
	{
		GLuint location = glGetUniformLocation(this->program, var);
		return location;
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
		GLchar infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				cout << "| ERROR::::SHADER-COMPILATION-ERROR of type: " << type << "|\n" << infoLog << "\n| -- --------------------------------------------------- -- |" << endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				cout << "| ERROR::::PROGRAM-LINKING-ERROR of type: " << type << "|\n" << infoLog << "\n| -- --------------------------------------------------- -- |" << endl;
			}
		}
	}

}
