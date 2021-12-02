class VertexBuffer;
class VertexBufferLayout;

#include "glad/glad.h"

#include <vector>

class VertexArray {
public:
	void add_buffer(const VertexBuffer &vb,
					const VertexBufferLayout &layout);

	void bind()   const;
	void unbind() const;

	VertexArray();
	~VertexArray();
	VertexArray(const VertexArray &other) = delete;
	VertexArray(VertexArray &&other) noexcept;
	
	VertexArray & operator=(const VertexArray &other) = delete;
	VertexArray & operator=(VertexArray &&other) noexcept;

private:
	GLuint _handle;

	std::vector<GLuint> _vertex_count;
};