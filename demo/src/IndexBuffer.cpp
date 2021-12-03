#include "IndexBuffer.hpp"

#include <algorithm>

void IndexBuffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _handle);
}

void IndexBuffer::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::IndexBuffer(const GLuint *data, const GLsizei count) :
	_handle{0},
	_count{count}
{
	glGenBuffers(1, &_handle);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				 static_cast<GLsizeiptr>(count * sizeof(GLuint)), data,
				 GL_STATIC_DRAW);
	unbind();
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &_handle);
}

IndexBuffer::IndexBuffer(IndexBuffer &&other) noexcept :
	_handle{0},
	_count{0}
{
	std::swap(_handle, other._handle);
	std::swap(_count,  other._count);
}

IndexBuffer & IndexBuffer::operator=(IndexBuffer &&other) noexcept {
	glDeleteBuffers(1, &_handle);
	_handle = 0;
	_count = 0;
	std::swap(_handle, other._handle);
	std::swap(_count,  other._count);

	return *this;
}