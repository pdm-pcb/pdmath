#ifndef RENDERER_HPP
#define RENDERER_HPP

class VertexArray;
class IndexBuffer;
class Shader;

class Renderer {
public:
	void draw(const VertexArray &va, const IndexBuffer &ib,
	          const Shader &shader) const;

	Renderer();
};

#endif // RENDERER_HPP