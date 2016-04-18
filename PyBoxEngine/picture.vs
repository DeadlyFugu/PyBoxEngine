#version 330 core

uniform vec2 pos;
uniform vec2 dim;
uniform mat3 view;

layout (location = 0) in vec2 position;

out vec2 _texco;

void main() {
	gl_Position = vec4(vec3(dim * position + pos, 1.0) * view , 1.0);
	_texco = position.xy;
}