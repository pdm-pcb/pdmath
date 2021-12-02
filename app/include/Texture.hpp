#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "glad/glad.h"

#include <string>

namespace PixelFormat {

constexpr GLint RGBA = 4;

} // namespace PixelFormat

class Texture {
public:
	void bind(GLint slot = 0);
	void unbind()              const;

	GLint texture_slot() const { return _slot; }

	Texture(const std::string &filepath);
	Texture() = delete;
	~Texture();
	Texture(const Texture &other) = delete;
	Texture(Texture &&other) noexcept;

	Texture & operator=(const Texture &other) = delete;
	Texture & operator=(Texture &&other) noexcept;

private:
	GLubyte *_buffer;
	GLuint   _handle;
	GLint    _width;
	GLint    _height;
	GLint    _bits_per_pixel;

	GLint    _slot;
};

#endif // TEXTURE_HPP