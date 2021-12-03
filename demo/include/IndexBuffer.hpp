#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP

#include "glad/glad.h"

#include <cstdint>

class IndexBuffer {
public:
	void bind()   const;
	void unbind() const;

	GLsizei count() const { return _count; }

	IndexBuffer(const GLuint *data, const GLsizei count);
	IndexBuffer() = delete;
	~IndexBuffer();
	IndexBuffer(const IndexBuffer &other) = delete;
	IndexBuffer(IndexBuffer &&other) noexcept;

	IndexBuffer & operator=(const IndexBuffer &other) = delete;
	IndexBuffer & operator=(IndexBuffer &&other) noexcept;

private:
	GLuint  _handle;
	GLsizei _count;
};

#endif // INDEXBUFFER_HPP