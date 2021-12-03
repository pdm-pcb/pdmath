#include "Renderer.hpp"

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

#include <cstring>

void Renderer::viewport(const GLint width, const GLint height) const {
    glViewport(0, 0,  width, height);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(const VertexArray &va, const IndexBuffer &ib,
					const Shader &shader) const {
    va.bind();
    ib.bind();
    shader.bind();
    glDrawElements(GL_TRIANGLES, ib.count(), GL_UNSIGNED_INT, nullptr);
}

Renderer::Renderer(const GLint width, const GLint height) {
    glClearColor(0.1f, 0.15f, 0.1f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    viewport(width, height);
}