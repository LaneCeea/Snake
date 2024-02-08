#version 460 core

layout (location = 0) in vec3 v_in_Position;
layout (location = 1) in vec4 v_in_Color;

out vec4 v_out_Color;

void main() {
    gl_Position = vec4(v_in_Position, 1.0f);
    v_out_Color = v_in_Color;
}
