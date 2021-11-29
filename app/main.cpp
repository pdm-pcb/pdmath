#include "Shader.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

constexpr int window_x = 1920;
constexpr int window_y = 1080;

void process_input(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height); 

int main() {
    // GLFW initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // create GLFW window
    GLFWwindow* window = glfwCreateWindow(window_x, window_y, "Learn OpenGL",
                                          nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    // let GLAD sort it out for us
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // shaders!
    Shader orange("../../app/shaders/orange.vert",
                  "../../app/shaders/orange.frag");

    //const char *vertex_source =
    //    "#version 460 core\n"
    //    "layout(location = 0) in vec3 position;\n"
    //    "void main() {\n"
    //    "    gl_Position = vec4(position.x, position.y, position.z, 1.0f);\n"
    //    "}\n";

    //const char *fragment_source =
    //    "#version 460 core\n"
    //    "out vec4 fragment_color;\n"
    //    "void main() {\n"
    //    "    fragment_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    //    "}\n";

    //FILE *outfile = fopen("../../app/shaders/orange_string.vert", "w");
    //fwrite(vertex_source, sizeof(char), strlen(vertex_source), outfile);
    //fclose(outfile);
    //outfile = fopen("../../app/shaders/orange_string.frag", "w");
    //fwrite(fragment_source, sizeof(char), strlen(fragment_source), outfile);
    //fclose(outfile);

    //Shader orange(vertex_source, fragment_source);

    //finally our first pure OpenGL command
    glViewport(0, 0, window_x, window_y);

    while(!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

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