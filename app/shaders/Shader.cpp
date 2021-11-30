#include "Shader.hpp"

#include <cassert>
#include <iostream>
#include <cstdio>

void Shader::use_program() const {
    glUseProgram(_program);
}

char * Shader::load_source(const std::string &filename) const
{
    if(filename.empty()) {
        std::cerr << "No file name provided to load_shader()" << std::endl;
        return nullptr;
    }

    FILE *input_file = fopen(filename.c_str(), "r");

    if(input_file == nullptr) {
        std::cerr << "Unable to open source '" << filename << "'" << std::endl;
        return nullptr;
    }

    fseek(input_file, 0, SEEK_END);
    size_t filesize = static_cast<size_t>(ftell(input_file));
    fseek(input_file, 0, SEEK_SET);

    char *shader_dest = new char[filesize + 1];

    fread(shader_dest, sizeof(char), filesize, input_file);
    fclose(input_file);

    shader_dest[filesize] = '\0';

    return shader_dest;
}

void Shader::create_program(const char *vertex_source,
                            const char *fragment_source) {
    _vertex_shader   = glCreateShader(GL_VERTEX_SHADER);
    _fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(_vertex_shader,   1, &vertex_source, nullptr);
    glShaderSource(_fragment_shader, 1, &fragment_source, nullptr);

    glCompileShader(_vertex_shader);
    glCompileShader(_fragment_shader);

    GLint vertex_status;
    GLint fragment_status;

    glGetShaderiv(_vertex_shader,   GL_COMPILE_STATUS, &vertex_status);
    glGetShaderiv(_fragment_shader, GL_COMPILE_STATUS, &fragment_status);

    if((vertex_status == GL_FALSE) || (fragment_status == GL_FALSE)) {
        glDeleteShader(_vertex_shader);
        glDeleteShader(_fragment_shader);

        return;
    }

    _program = glCreateProgram();
    glAttachShader(_program, _vertex_shader);
    glAttachShader(_program, _fragment_shader);
    glLinkProgram(_program);

    glDeleteShader(_vertex_shader);
    glDeleteShader(_fragment_shader);

    GLint program_status;
    glGetProgramiv(_program, GL_LINK_STATUS, &program_status);

    if(program_status == GL_FALSE) {
        glDeleteProgram(_program);

        return;
    }
}

Shader::Shader(const std::string &vertex_filename,
               const std::string &fragment_filename) noexcept :
    _vertex_shader{0},
    _fragment_shader{0},
    _program{0}
{
    char *vertex_source   = load_source(vertex_filename);
    char *fragment_source = load_source(fragment_filename);
    
    create_program(vertex_source,  fragment_source);

    delete[] vertex_source;
    delete[] fragment_source;
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