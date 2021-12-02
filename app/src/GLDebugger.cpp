#include "GLDebugger.hpp"

#include <iostream>

void GLAPIENTRY
    GLDebugger::error_callback(GLenum source,
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

    std::cerr << "\n[OpenGL] " << _type << " #" << id << " (Severity: "
        << _severity << ")" << " from " << _source << "\n---\n"
        << message << "\n---"
        << std::endl;
}

GLDebugger::GLDebugger() {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(&error_callback, nullptr);

    std::ios_base::sync_with_stdio(false);
}