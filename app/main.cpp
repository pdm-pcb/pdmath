#include "Shader.hpp"
#include "Texture.hpp"
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

constexpr GLfloat square[] = {
    // world coordinates    texture coordinates
    -0.25f,  0.5f, 0.0f,    0.0f, 1.0f,    // top left
     0.25f,  0.5f, 0.0f,    1.0f, 1.0f,    // top right
     0.25f, -0.5f, 0.0f,    1.0f, 0.0f,    // bottom right
    -0.25f, -0.5f, 0.0f,    0.0f, 0.0f     // bottom left
};

constexpr GLuint indices[] = {
    0, 1, 2,    // upper triangle
    0, 2, 3     // lower triangle
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

    // buffers
    VertexArray va;
    VertexBuffer vb(square, sizeof(square));
    vb.set_layout({
        { "world_coordinates",   GL_FLOAT, 3, GL_FALSE },
        { "texture_coordinates", GL_FLOAT, 2, GL_FALSE }
    });
    va.add_buffer(vb);
    IndexBuffer ib(indices, 6);

    // shaders!
    Shader crate0_shader("../../app/shaders/crate.vert",
                         "../../app/shaders/crate0.frag");

    // textures!
    Texture crate0_texture("../../app/resources/textures/crate1/crate1.png");
    crate0_texture.bind();
    crate0_shader.set_uniform1i("texture_slot", crate0_texture.texture_slot());

    glViewport(0, 0, window_x, window_y);

    Renderer renderer;

    while(!glfwWindowShouldClose(window)) {
        process_input(window);

        glClear(GL_COLOR_BUFFER_BIT);

        renderer.draw(va, ib, crate0_shader);

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