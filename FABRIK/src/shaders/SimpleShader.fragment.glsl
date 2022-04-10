#version 430 core

layout (location = 0) out vec4 color;

in vec4 frag_color;

void main(void) {
        color = frag_color;
}
