#version 330

in vec3 v_color;

out vec4 frag_color;

void main(void) {
    frag_color.rgb = v_color;
}