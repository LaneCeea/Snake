#version 460 core

out vec4 f_Color;

uniform vec4 u_Color;

void main() {
	f_Color = u_Color;
}
