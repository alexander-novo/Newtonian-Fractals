#version 330

layout (location = 0) in vec3 vert;
layout (location = 1) in vec3 color;

out vec3 v_color;

void main(void) {
    gl_Position = vec4(vert, 1.0);
    v_color = color;
}