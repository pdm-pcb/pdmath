#include "Renderer.hpp"

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

#include <iostream>
#include <cstring>

void Renderer::draw(const VertexArray &va, const IndexBuffer &ib,
					const Shader &shader) const {
    va.bind();
    ib.bind();
    shader.bind();
    glDrawElements(GL_TRIANGLES, ib.count(), GL_UNSIGNED_INT, nullptr);
}

Renderer::Renderer() {
    std::cout << glGetString(GL_VERSION) << " : "
              << glGetString(GL_RENDERER)
              << std::endl;

    glClearColor(0.1f, 0.15f, 0.1f, 1.0f);
}