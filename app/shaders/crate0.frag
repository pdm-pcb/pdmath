#version 460 core

in vec2 tex_coord;
uniform sampler2D texture_slot;

out vec4 color;

void main() {
	color = texture(texture_slot, tex_coord);
}