#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

uniform mat4 u_Mvp;

void main() {
    gl_Position = u_Mvp * vec4(a_Position, 1.0f);
    v_TexCoord = a_TexCoord;
}
