#version 430 core

layout (location = 0) in vec4 in_position;
layout (location = 1) in vec4 in_color;

out vec4 frag_color;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main(void) {
        gl_Position = (projection_matrix * view_matrix * model_matrix) * in_position;
        frag_color = in_color;
}
