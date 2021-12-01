class VertexBuffer;
class VertexBufferLayout;

#include "glad/glad.h"

class VertexArray {
public:
	void add_buffer(const VertexBuffer &vb,
					const VertexBufferLayout &layout);

	void bind()   const;
	static void unbind();

	VertexArray();
	~VertexArray();

private:
	GLuint _handle;
};