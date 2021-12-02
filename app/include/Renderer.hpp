#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "glad/glad.h"

class VertexArray;
class IndexBuffer;
class Shader;

void GLAPIENTRY error_callback(GLenum source,
						       GLenum type, GLuint id, GLenum severity,
						       GLsizei length, const GLchar *message,
						       const void *user_data);
class Renderer {
public:
	void draw(const VertexArray &va, const IndexBuffer &ib,
	          const Shader &shader) const;

	Renderer();
};

#endif // RENDERER_HPP