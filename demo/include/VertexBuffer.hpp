#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include "VertexBufferLayout.hpp"

#include "glad/glad.h"

#include <cstdint>

class VertexBuffer {
public:
	void bind()   const;
	void unbind() const;

	void set_layout(const element_list &elements);

	const VertexBufferLayout * layout() const { return _layout; }

	VertexBuffer(const GLfloat *data, const uint32_t size);
	VertexBuffer() = delete;
	~VertexBuffer();
	VertexBuffer(const VertexBuffer &other) = delete;
	VertexBuffer(VertexBuffer &&other) noexcept;

	VertexBuffer & operator=(const VertexBuffer &other) = delete;
	VertexBuffer & operator=(VertexBuffer &&other) noexcept;

private:
	GLuint _handle;
	VertexBufferLayout *_layout;
};

#endif // VERTEXBUFFER_HPP