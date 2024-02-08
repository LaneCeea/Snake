#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;

out vec4 v_Color;

uniform mat4 u_Mvp;

void main() {
    gl_Position = u_Mvp * vec4(a_Position, 1.0f);
    v_Color = a_Color;
}
