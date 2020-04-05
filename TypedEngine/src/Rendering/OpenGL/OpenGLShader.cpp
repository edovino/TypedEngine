#include "OpenGLShader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

OpenGLShader::OpenGLShader(const char * path) {
	parseShader(path, &source);

	rendererID = glCreateProgram();
	GLuint v = createShader(ShaderType::VERTEX);
	GLuint f = createShader(ShaderType::FRAGMENT);
	glAttachShader(rendererID, v);
	glAttachShader(rendererID, f);
	glLinkProgram(rendererID);
	glValidateProgram(rendererID);

	glDetachShader(rendererID, v);
	glDetachShader(rendererID, f);
}

OpenGLShader::~OpenGLShader() {
	glDeleteProgram(rendererID);
}

void OpenGLShader::run() {
	glUseProgram(rendererID);
}

void OpenGLShader::setUniformFloat4(const char * name, glm::vec4 value) {
	glUniform4f(glGetUniformLocation(rendererID, name), value.x, value.y, value.z, value.w);
}

void OpenGLShader::setUniformMat4(const char * name, glm::mat4 value) {
	glUniformMatrix4fv(glGetUniformLocation(rendererID, name), 1, GL_FALSE, &value[0][0]);
}

void OpenGLShader::setUniformSampler(const char * name, int id) {
	glUniform1i(glGetUniformLocation(rendererID, name), id);
}

unsigned int OpenGLShader::createShader(ShaderType type) {
	GLenum enumType;
	const char* sourceType;

	switch (type) {
		case ShaderType::VERTEX: {
			enumType = GL_VERTEX_SHADER;
			sourceType = source.vertex;
			break;
		}
		case ShaderType::FRAGMENT: {
			enumType = GL_FRAGMENT_SHADER;
			sourceType = source.fragment;
			break;
		}
	}

	GLuint result = glCreateShader(enumType);
	glShaderSource(result, 1, &sourceType, NULL);
	glCompileShader(result);

	GLint iv;
	glGetShaderiv(result, GL_COMPILE_STATUS, &iv);
	if (iv == GL_FALSE) {
		int length;
		glGetShaderiv(result, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(result, length, &length, message);
		std::cout << message << std::endl;
		glDeleteShader(result);
	}
	return result;
}