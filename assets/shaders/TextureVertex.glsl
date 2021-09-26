#version 460 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_texCoords;

uniform mat4 u_viewProjectionMatrix;
out vec2 v_texCoords;

void main() {
    gl_Position = u_viewProjectionMatrix * vec4(a_pos, 1.0);
    v_texCoords = a_texCoords;
}
