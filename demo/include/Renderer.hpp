#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "glad/glad.h"

class VertexArray;
class IndexBuffer;
class Shader;

class Renderer {
public:
	void viewport(const GLint width, const GLint height) const;
	void draw(const VertexArray &va, const IndexBuffer &ib,
	          const Shader &shader) const;

	Renderer(const GLint width, const GLint height);
};

#endif // RENDERER_HPP