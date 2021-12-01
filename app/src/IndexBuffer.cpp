#include "IndexBuffer.hpp"

#include <algorithm>

void IndexBuffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _handle);
}

void IndexBuffer::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::IndexBuffer(const GLuint *data, const uint32_t count) :
	_handle{0},
	_count{count}
{
	glGenVertexArrays(1, &_handle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _handle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data,
				 GL_STATIC_DRAW);
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