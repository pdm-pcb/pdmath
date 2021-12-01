#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP

#include "glad/glad.h"

#include <cstdint>

class IndexBuffer {
public:
	void bind()   const;
	static void unbind();

	IndexBuffer(const GLuint *data, const uint32_t count);
	IndexBuffer() = delete;
	~IndexBuffer();
	IndexBuffer(const IndexBuffer &other) = delete;
	IndexBuffer(IndexBuffer &&other) noexcept;

	IndexBuffer & operator=(const IndexBuffer &other) = delete;
	IndexBuffer & operator=(IndexBuffer &&other) noexcept;

private:
	GLuint _handle;
	GLuint _count;
};

#endif // INDEXBUFFER_HPP