#pragma once

#include "../Shader.h"

enum class ShaderType : uint8_t {
	NONE = -1, VERTEX = 0, FRAGMENT = 1
};

class OpenGLShader : public Shader {
public:
	OpenGLShader(const char* path);
	~OpenGLShader();
	virtual void run() override;

	virtual void setUniformFloat4(const char * name, glm::vec4 value) override;
	virtual void setUniformMat4(const char * name, glm::mat4 value) override;
	virtual void setUniformSampler(const char * name, int id) override;

private:
	unsigned int createShader(ShaderType type);
};