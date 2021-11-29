#include "Shader.hpp"

#include <cassert>
#include <iostream>
#include <cstdio>

void Shader::use_program() const {
    if(_program != 0) {
        glUseProgram(_program);
    }
    else {
        std::cerr << "Shader in an unusable state" << std::endl;
    }
}

void Shader::load_source(const std::string &filename, char *shader_dest) const
{
    if(filename.empty()) {
        std::cerr << "No file name provided to load_shader()" << std::endl;
        return;
    }

    if(shader_dest != nullptr) {
        std::cerr << "Shader source destination may not be free" << std::endl;
        return;
    }

    FILE *input_file = fopen(filename.c_str(), "rt");

    if(input_file == nullptr) {
        std::cerr << "Unable to open source '" << filename << "'" << std::endl;
        return;
    }

    fseek(input_file, 0, SEEK_END);
    size_t filesize = static_cast<size_t>(ftell(input_file));
    fseek(input_file, 0, SEEK_SET);

    shader_dest = new char[filesize + 1];

    fread(shader_dest, sizeof(char), filesize, input_file);
    fclose(input_file);

    shader_dest[filesize] = '\0';

    return;
}

void Shader::create_program(const char *vertex_source,
                            const char *fragment_source) {
    _vertex_shader   = glCreateShader(GL_VERTEX_SHADER);
    _fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(_vertex_shader,   1, &vertex_source, nullptr);
    glShaderSource(_fragment_shader, 1, &fragment_source, nullptr);

    glCompileShader(_vertex_shader);
    GLenum error = glGetError();
    if(error != GL_NO_ERROR) {
        std::cerr << " GLError " << error << " on vertex shader compile"
                  << std::endl;
    }

    glCompileShader(_fragment_shader);
    error = glGetError();
    if(error != GL_NO_ERROR) {
        std::cerr << " GLError " << error << " on fragment shader compile"
                  << std::endl;
    }

    GLint vertex_status;
    GLint fragment_status;

    glGetShaderiv(_vertex_shader,   GL_COMPILE_STATUS, &vertex_status);
    glGetShaderiv(_fragment_shader, GL_COMPILE_STATUS, &fragment_status);

    if((vertex_status == GL_FALSE) || (fragment_status == GL_FALSE)) {
        compile_error();

        glDeleteShader(_vertex_shader);
        glDeleteShader(_fragment_shader);

        return;
    }

    _program = glCreateProgram();
    glAttachShader(_program, _vertex_shader);
    glAttachShader(_program, _fragment_shader);
    glLinkProgram(_program);

    error = glGetError();
    if(error != GL_NO_ERROR) {
        std::cerr << " GLError - " << error << " on shader link" << std::endl;
    }

    glDeleteShader(_vertex_shader);
    glDeleteShader(_fragment_shader);

    GLint program_status;
    glGetProgramiv(_program, GL_LINK_STATUS, &program_status);

    if(program_status == GL_FALSE) {
        link_error();

        glDeleteProgram(_program);

        return;
    }
}

void Shader::compile_error() const {
    GLint vertex_log_length   = 0;
    GLint fragment_log_length = 0;

    glGetShaderiv(_vertex_shader, GL_INFO_LOG_LENGTH, &vertex_log_length);
    glGetShaderiv(_fragment_shader, GL_INFO_LOG_LENGTH, &fragment_log_length);

    std::cerr << "Something went wrong compiling the shaders!\n";

    if(vertex_log_length > 1) {
        GLchar *shader_log =
            new GLchar[(static_cast<size_t>(vertex_log_length) + 1)];
        glGetShaderInfoLog(_vertex_shader, vertex_log_length, nullptr,
                           shader_log);
        std::cerr << "Vertex Log:\n---\n"
                  << shader_log << "\n---" << std::endl;
        delete[] shader_log;
    }

    if(fragment_log_length > 1) {
        GLchar *shader_log =
            new GLchar[(static_cast<size_t>(fragment_log_length) + 1)];
        glGetShaderInfoLog(_fragment_shader, fragment_log_length, nullptr,
                           shader_log);
        std::cerr << "Fragment Log:\n---\n"
                  << shader_log << "\n---" << std::endl;
        delete[] shader_log;
    }
}

void Shader::link_error() const {
    GLint linker_log_length = 0;
    glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &linker_log_length);

    std::cerr << "Something went wrong linking the shaders!\n";

    if(linker_log_length > 1) {
        GLchar *linker_log =
            new GLchar[(static_cast<size_t>(linker_log_length) + 1)];
        glGetProgramInfoLog(_program, linker_log_length, nullptr, linker_log);
        std::cerr << "Linker Log:\n---\n"
                  << linker_log << "\n---" << std::endl;
        delete[] linker_log;
    }
}

Shader::Shader(const std::string &vertex_filename,
               const std::string &fragment_filename) noexcept :
    _vertex_shader{0},
    _fragment_shader{0},
    _program{0}
{
    char *vertex_source   = nullptr;
    char *fragment_source = nullptr;

    load_source(vertex_filename,   vertex_source);
    load_source(fragment_filename, fragment_source);
    create_program(vertex_source,  fragment_source);

    delete[] vertex_source;
    delete[] fragment_source;
}

Shader::Shader(const char *vertex_source,
               const char *fragment_source) noexcept :
    _vertex_shader{0},
    _fragment_shader{0},
    _program{0}
{
    create_program(vertex_source, fragment_source);
}

Shader::~Shader() {
    glDeleteShader(_vertex_shader);
    glDeleteShader(_fragment_shader);
    glDeleteProgram(_program);
}

Shader::Shader(Shader &&other) noexcept:
    _vertex_shader{0},
    _fragment_shader{0},
    _program{0}
{
    std::swap(_vertex_shader,   other._vertex_shader);
    std::swap(_fragment_shader, other._fragment_shader);
    std::swap(_program,         other._program);
}

Shader& Shader::operator=(Shader &&other) noexcept {
    glDeleteShader(_vertex_shader);
    glDeleteShader(_fragment_shader);
    glDeleteProgram(_program);

    _vertex_shader   = 0;
    _fragment_shader = 0;
    _program         = 0;

    std::swap(_vertex_shader,   other._vertex_shader);
    std::swap(_fragment_shader, other._fragment_shader);
    std::swap(_program,         other._program);

    return *this;
}