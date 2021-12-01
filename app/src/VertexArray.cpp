#include "VertexArray.hpp"

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

#include <algorithm>

void VertexArray::add_buffer(const VertexBuffer &vb,
							 const VertexBufferLayout &layout)
{
	GLuint offset = 0;

	bind();
	vb.bind();

	const auto &elements = layout.elements();
	for(GLuint el_index = 0; el_index < elements.size(); el_index++) {
		const auto &element = elements[el_index];

		glVertexAttribPointer(el_index, element.count, element.type,
							  element.normalized, layout.stride(),
							  static_cast<const void *>(&offset));

		glEnableVertexAttribArray(el_index);

		offset += element.count * sizeof(element.type);
	}
}

void VertexArray::bind() const {
	glBindVertexArray(_handle);
}

void VertexArray::unbind() {
	glBindVertexArray(0);
}

VertexArray::VertexArray() {
	glGenVertexArrays(1, &_handle);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &_handle);
}
