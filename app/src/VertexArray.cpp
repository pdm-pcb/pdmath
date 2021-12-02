#include "VertexArray.hpp"

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

#include <algorithm>

void VertexArray::add_buffer(const VertexBuffer &vb) {
	bind();
	vb.bind();

	const auto *layout   = vb.layout();
	const auto &elements = layout->elements();
	for(GLuint el_index = 0; el_index < elements.size(); el_index++) {
		const auto &element = elements[el_index];

		glVertexAttribPointer(el_index, element._count, element._type,
							  element._normalized, layout->stride(),
							  reinterpret_cast<void *>(element._offset));

		glEnableVertexAttribArray(el_index);
	}

	vb.unbind();
	unbind();
}

void VertexArray::bind() const {
	glBindVertexArray(_handle);
}

void VertexArray::unbind() const {
	glBindVertexArray(0);
}

VertexArray::VertexArray() {
	glGenVertexArrays(1, &_handle);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &_handle);
}
