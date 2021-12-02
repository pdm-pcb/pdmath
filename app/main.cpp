#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Renderer.hpp"
#include "GLDebugger.hpp"

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

    // Enable debug output
    GLDebugger debugger;

    // triangle a
    VertexArray va_a;
    VertexBuffer vb_a(triangle_a, sizeof(triangle_a));
    vb_a.set_layout({
        { "position", GL_FLOAT, 3, GL_FALSE }
    });
    va_a.add_buffer(vb_a);
    IndexBuffer ib_a(indices_a, 3);

    // triangle b
    VertexArray va_b;
    VertexBuffer vb_b(triangle_b, sizeof(triangle_b));
    vb_b.set_layout({
        { "position", GL_FLOAT, 3, GL_FALSE }
    });
    va_b.add_buffer(vb_b);
    IndexBuffer ib_b(indices_b, 3);

    // shaders!
    Shader orange("../../app/shaders/colored_shape.vert",
                  "../../app/shaders/orange.frag");
    Shader blue("../../app/shaders/colored_shape.vert",
                "../../app/shaders/blue.frag");

    glViewport(0, 0, window_x, window_y);

    Renderer renderer;

    while(!glfwWindowShouldClose(window)) {
        process_input(window);

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