#version 460 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec4 a_color;
//layout (location = 2) in vec2 a_texCoord;

uniform mat4 u_viewProjectionMatrix;
uniform mat4 u_modelMatrix;

out vec4 v_color;

void main() {
    gl_Position = u_viewProjectionMatrix * u_modelMatrix * vec4(a_pos, 1.0);
    v_color = a_color;
}
