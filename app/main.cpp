#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "IndexBuffer.hpp"
#include "Renderer.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

constexpr int window_x = 1920;
constexpr int window_y = 1080;

constexpr GLfloat triangle_a[] = {
    -0.25f,  0.5f,  0.0f,
    -0.5f,  -0.25f, 0.0f,
    -0.75f,  0.5f,  0.0f,
};

constexpr GLfloat triangle_b[] = {
     0.5f,   0.5f,  0.0f,
     0.75f, -0.25f, 0.0f,
     0.25f, -0.25f, 0.0f
};

constexpr GLuint indices_a[] = {
    0, 1, 2
};

constexpr GLuint indices_b[] = {
    0, 1, 2
};

void process_input(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() {
    // GLFW initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    // create GLFW window
    GLFWwindow* window = glfwCreateWindow(window_x, window_y, "Learn OpenGL",
                                          nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    // let GLAD sort it out for us
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << " : "
              << glGetString(GL_RENDERER)
              << std::endl;

    // Enable debug output
    Renderer renderer;

    // triangle a
    VertexArray va_a;
    VertexBuffer vb_a(triangle_a, sizeof(triangle_a));
    VertexBufferLayout layout_a;
    layout_a.push<GLfloat>(3);
    IndexBuffer ib_a(indices_a, 3);
    va_a.add_buffer(vb_a, layout_a);

    // triangle b
    VertexArray va_b;
    VertexBuffer vb_b(triangle_b, sizeof(triangle_b));
    VertexBufferLayout layout_b;
    layout_a.push<GLfloat>(3);
    IndexBuffer ib_b(indices_b, 3);
    va_b.add_buffer(vb_b, layout_b);

    // shaders!
    Shader orange("../../app/shaders/colored_shape.vert",
                  "../../app/shaders/orange.frag");
    Shader blue("../../app/shaders/colored_shape.vert",
                "../../app/shaders/blue.frag");

    glViewport(0, 0, window_x, window_y);

    while(!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.draw(va_a, ib_a, orange);
        renderer.draw(va_b, ib_b, blue);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
  
    return 0;
}

void process_input(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}