#include "Texture.hpp"

#include "stb/stb_image.h"

void Texture::bind(GLint slot) {
	_slot = slot;
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, _handle);
}

void Texture::unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const std::string &filepath) :
	_buffer{nullptr}, _handle{0},
	_width{0}, _height{0}, _bits_per_pixel{0},
	_slot{-1}
{
	static_assert(GL_TEXTURE1 - GL_TEXTURE0 == 1);

	stbi_set_flip_vertically_on_load(true);
	_buffer = stbi_load(filepath.c_str(), &_width, &_height,
						&_bits_per_pixel, PixelFormat::RGBA);

	glGenTextures(1, &_handle);
	bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
					GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA,
				 GL_UNSIGNED_BYTE, _buffer);
	glGenerateMipmap(GL_TEXTURE_2D);
	unbind();

	if(_buffer) {
		stbi_image_free(_buffer);
		_buffer = nullptr;
	}
}

Texture::~Texture() {
	glDeleteTextures(1, &_handle);
}

Texture::Texture(Texture &&other) noexcept :
	_buffer{nullptr}, _handle{0},
	_width{0}, _height{0}, _bits_per_pixel{0},
	_slot{-1}
{
	std::swap(_buffer, other._buffer);
	std::swap(_handle, other._handle);
	std::swap(_width,  other._width);
	std::swap(_height, other._height);
	std::swap(_bits_per_pixel, other._bits_per_pixel);
	std::swap(_slot,   other._slot);
}

Texture & Texture::operator=(Texture &&other) noexcept
{
	if(_buffer) {
		stbi_image_free(_buffer);
		_buffer = nullptr;
	}

	_height = 0;
	_width  = 0;
	_bits_per_pixel = 0;
	_slot   = -1;

	glDeleteTextures(1, &_handle);
	_handle = 0;

	std::swap(_buffer, other._buffer);
	std::swap(_handle, other._handle);
	std::swap(_width,  other._width);
	std::swap(_height, other._height);
	std::swap(_bits_per_pixel, other._bits_per_pixel);
	std::swap(_slot,   other._slot);

	return *this;
}