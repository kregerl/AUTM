#version 460 core
layout (location = 0) in vec3 a_pos;

uniform mat4 u_viewProjectionMatrix;
uniform mat4 u_modelMatrix;

void main() {
    gl_Position = u_viewProjectionMatrix * u_modelMatrix * vec4(a_pos, 1.0);
}
