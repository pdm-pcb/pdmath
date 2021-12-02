#version 460 core

layout(location = 0) in vec3 world_coordinates;
layout(location = 1) in vec2 texture_coordinates;

out vec2 tex_coord;

uniform mat4 ortho_proj;

void main() {
	gl_Position = ortho_proj * vec4(world_coordinates, 1.0f);
	tex_coord = texture_coordinates;
}