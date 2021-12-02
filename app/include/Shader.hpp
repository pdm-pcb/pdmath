#ifndef SHADER_HPP
#define SHADER_HPP

#include "glad/glad.h"

#include <string>
#include <unordered_map>

class Shader {
public:
    void bind()   const;
    void unbind() const;

    void set_uniform1i(const std::string &name, const GLint value);
    void set_uniform1f(const std::string &name, const GLfloat value);
    void set_uniform4f(const std::string &name,
                       const GLfloat v0, const GLfloat v1, const GLfloat v2,
                       const GLfloat v3);

    GLint get_uniform_handle(const std::string &name);

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

    std::unordered_map<std::string, GLint> _uniform_cache;

    char * load_source(const std::string &filename) const;
    void create_program(const char *vertex_source,
                        const char *fragment_source);
};

#endif //SHADER_HPP
