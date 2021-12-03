#include "VertexBuffer.hpp"

#include <algorithm>

void VertexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, _handle);
}

void VertexBuffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::set_layout(const element_list &elements) {
	_layout = new VertexBufferLayout(elements);
}

VertexBuffer::VertexBuffer(const GLfloat *data, const uint32_t size) :
	_handle{0},
	_layout{nullptr}
{
	glGenBuffers(1, &_handle);
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	unbind();
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &_handle);
	delete _layout;
}

VertexBuffer::VertexBuffer(VertexBuffer &&other) noexcept :
	_handle{0},
	_layout{nullptr}
{
	std::swap(_handle, other._handle);
	std::swap(_layout, other._layout);
}

VertexBuffer & VertexBuffer::operator=(VertexBuffer &&other) noexcept {
	glDeleteBuffers(1, &_handle);
	delete _layout;

	_handle = 0;
	_layout = 0;

	std::swap(_handle, other._handle);
	std::swap(_layout, other._layout);

	return *this;
}
