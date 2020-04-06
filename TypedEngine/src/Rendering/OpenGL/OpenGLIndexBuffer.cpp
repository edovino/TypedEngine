#include "OpenGLIndexBuffer.h"

#include "GL/glew.h"

OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, unsigned int size) {
	glGenBuffers(1, &rendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
	count = size;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indices, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer() {
}

void OpenGLIndexBuffer::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
}

void OpenGLIndexBuffer::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int OpenGLIndexBuffer::getCount() const {
	return count;
}
