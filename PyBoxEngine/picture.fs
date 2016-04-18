#version 330 core

in vec2 _texco;

out vec4 color;

uniform sampler2D _tex;

void main() {
	color = texture(_tex, vec2(_texco.x, 1-_texco.y));
}