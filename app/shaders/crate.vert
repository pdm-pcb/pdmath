#version 460 core

layout(location = 0) in vec4 world_coordinates;
layout(location = 1) in vec2 texture_coordinates;

out vec2 tex_coord;

void main() {
	gl_Position = world_coordinates;
	tex_coord = texture_coordinates;
}