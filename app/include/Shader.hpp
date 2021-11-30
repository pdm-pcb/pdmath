#ifndef SHADER_HPP
#define SHADER_HPP

#include "glad/glad.h"

#include <string>

class Shader {
public:
    void use_program() const;

    Shader(const std::string &vertex_filename,
           const std::string &fragment_filename) noexcept;
    Shader() = delete;
    ~Shader();
    Shader(const Shader &other) = delete;
    Shader(Shader &&other) noexcept;

    Shader& operator=(const Shader &other) = delete;
    Shader& operator=(Shader &&other) noexcept;

private:
    GLuint  _vertex_shader;
    GLuint  _fragment_shader;
    GLuint  _program;

    char * load_source(const std::string &filename) const;
    void create_program(const char *vertex_source,
                        const char *fragment_source);
    void compile_error() const;
    void link_error()    const;
};

#endif //SHADER_HPP
