#ifndef VERTEXBUFFERLAYOUT_HPP
#define VERTEXBUFFERLAYOUT_HPP

#include "glad/glad.h"

#include <vector>
#include <string>

struct VertexBufferElement {
	std::string _name;
	GLuint      _type;
	GLint       _count;
	GLuint      _size;
	GLuint      _offset;
	GLboolean   _normalized;

	VertexBufferElement(const std::string &name, const GLuint type,
						const GLint count, const GLboolean normalized) :
		_name{name},
		_type{type},
		_count{count},
		_size{count * sizeof(type)},
		_offset{0},
		_normalized{normalized}
	{ }
};

using element_list = std::initializer_list<VertexBufferElement>;

class VertexBufferLayout {
public:
	const std::vector<VertexBufferElement> & elements() const {
		return _elements;
	}
	GLuint stride() const { return _stride; }

	VertexBufferLayout() = default;
	VertexBufferLayout(const element_list &elements) :
		_elements{elements}, _stride { 0 }
	{
		calculate_offset_and_stride();
	}

private:
	std::vector<VertexBufferElement> _elements;
	GLuint _stride;

	void calculate_offset_and_stride() {
		GLuint offset = 0;
		_stride = 0;

		for(auto &element : _elements) {
			element._offset = offset;
			offset  += element._size;
			_stride += element._size;
		}
	}
};

#endif // VERTEXBUFFERLAYOUT_HPP