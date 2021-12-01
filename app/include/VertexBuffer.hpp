#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include "glad/glad.h"

#include <cstdint>

class VertexBuffer {
public:
	void bind()   const;
	static void unbind();

	VertexBuffer(const GLfloat *data, const uint32_t size);
	VertexBuffer() = delete;
	~VertexBuffer();
	VertexBuffer(const VertexBuffer &other) = delete;
	VertexBuffer(VertexBuffer &&other) noexcept;

	VertexBuffer & operator=(const VertexBuffer &other) = delete;
	VertexBuffer & operator=(VertexBuffer &&other) noexcept;

private:
	GLuint _handle;
};

#endif // VERTEXBUFFER_HPP