#include "VertexBuffer.hpp"
#include "..\include\VertexBuffer.hpp"

#include <algorithm>

void VertexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, _handle);
}

void VertexBuffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::VertexBuffer(const GLfloat *data, const uint32_t size) :
	_handle{0}
{
	glGenBuffers(1, &_handle);
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	unbind();
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &_handle);
}

VertexBuffer::VertexBuffer(VertexBuffer &&other) noexcept :
	_handle{0}
{
	std::swap(_handle, other._handle);
}

VertexBuffer & VertexBuffer::operator=(VertexBuffer &&other) noexcept {
	glDeleteBuffers(1, &_handle);
	_handle = 0;
	std::swap(_handle, other._handle);

	return *this;
}
