#ifndef VERTEXBUFFERLAYOUT_HPP
#define VERTEXBUFFERLAYOUT_HPP

#include "glad/glad.h"

#include <vector>
#include <cstdint>

struct VertexBufferElement {
	GLuint    type;
	GLuint    count;
	GLboolean normalized;
};

class VertexBufferLayout {
public:
	template<typename T>
	void push(GLuint count) {
		static_assert(false);
	}

	template<>
	void push<GLfloat>(GLuint count) {
		_elements.push_back({GL_FLOAT, count, GL_FALSE});
		_stride += sizeof(GLfloat) * count;
	}

	inline const std::vector<VertexBufferElement> & elements() const {
		return _elements;
	}
	inline GLuint stride() const { return _stride; }

	VertexBufferLayout() :
		_stride{0}
	{ }

private:
	std::vector<VertexBufferElement> _elements;
	GLuint _stride;
};

#endif // VERTEXBUFFERLAYOUT_HPP