#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <cstring>

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

void process_input(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void GLAPIENTRY error_callback(GLenum source,
                               GLenum type, GLuint id, GLenum severity,
                               GLsizei length, const GLchar *message,
                               const void *user_data);

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
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << " : "
              << glGetString(GL_RENDERER)
              << std::endl;

    // Enable debug output
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(error_callback, nullptr);

    // shaders!
    Shader orange("../../app/shaders/colored_shape.vert",
                  "../../app/shaders/orange.frag");
    Shader blue("../../app/shaders/colored_shape.vert",
                "../../app/shaders/blue.frag");

    // buffers
    GLuint vao[2];
    GLuint vbo[2];

    glGenVertexArrays(2, vao);
    glGenBuffers(2, vbo);

    // triangle a
    //glBindVertexArray(vao[0]);

    //glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_a), triangle_a, GL_STATIC_DRAW);

    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    //glEnableVertexAttribArray(0);

    VertexBuffer vb_a(triangle_a, sizeof(triangle_a));
    VertexBufferLayout layout_a;
    layout_a.push<GLfloat>(3);
    VertexArray va_a;
    va_a.add_buffer(vb_a, layout_a);

    // triangle b
    //glBindVertexArray(vao[1]);

    //glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_b), triangle_b, GL_STATIC_DRAW);

    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    //glEnableVertexAttribArray(0);

    VertexBuffer vb_b(triangle_b, sizeof(triangle_b));
    VertexBufferLayout layout_b;
    layout_b.push<GLfloat>(3);
    VertexArray va_b;
    va_b.add_buffer(vb_b, layout_b);

    glViewport(0, 0, window_x, window_y);

    while(!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        orange.bind();
        va_a.bind();
        //glBindVertexArray(vao[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        blue.bind();
        va_b.bind();
        //glBindVertexArray(vao[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(2, vao);
    glDeleteBuffers(2, vbo);
  
    return 0;
}

void process_input(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}


void GLAPIENTRY error_callback(GLenum source,
                               GLenum type, GLuint id, GLenum severity,
                               GLsizei length, const GLchar *message,
                               const void *user_data) {
    const char *_severity;
    const char *_source;
    const char *_type;

    switch(severity) {
    case GL_DEBUG_SEVERITY_HIGH:
        _severity = "High";
        break;

    case GL_DEBUG_SEVERITY_MEDIUM:
        _severity = "Medium";
        break;

    case GL_DEBUG_SEVERITY_LOW:
        _severity = "Low";
        break;

    case GL_DEBUG_SEVERITY_NOTIFICATION:
        _severity = "Notification";
        break;

    default:
        _severity = "Unknown";
        break;
    }

    switch(source) {
        case GL_DEBUG_SOURCE_API:
            _source = "API";
            break;

        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            _source = "Window System";
            break;

        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            _source = "Shader Compiler";
            break;

        case GL_DEBUG_SOURCE_THIRD_PARTY:
            _source = "Third Party";
            break;

        case GL_DEBUG_SOURCE_APPLICATION:
            _source = "Application";
            break;

        case GL_DEBUG_SOURCE_OTHER:
            _source = "Other";
            break;

        default:
            _source = "Unknown";
            break;
    }

    switch(type) {
        case GL_DEBUG_TYPE_ERROR:
            _type = "Error";
            break;

        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            _type = "Depricated Behavior";
            break;

        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            _type = "Undefined Behavior";
            break;

        case GL_DEBUG_TYPE_PORTABILITY:
            _type = "Portability";
            break;

        case GL_DEBUG_TYPE_PERFORMANCE:
            _type = "Performance";
            break;

        case GL_DEBUG_TYPE_OTHER:
            _type = "Other";
            break;

        case GL_DEBUG_TYPE_MARKER:
            _type = "Marker";
            break;

        default:
            _type = "Unknown";
            break;
    }

    std::cerr << "\nOpenGL: " << _type << " #" << id << " (Severity: "
              << _severity << ")" << " from " << _source << "\n---\n"
              << message << "\n---"
              << std::endl;
}