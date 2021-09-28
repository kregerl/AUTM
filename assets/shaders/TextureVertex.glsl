#version 460 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_texCoord;
layout (location = 2) in vec3 a_color;
layout (location = 3) in float a_tilingFactor;

uniform mat4 u_viewProjectionMatrix;
uniform mat4 u_modelMatrix;

out vec2 v_texCoords;
out vec3 v_color;
out float v_tilingFactor;

void main() {
    gl_Position = u_viewProjectionMatrix * u_modelMatrix * vec4(a_pos, 1.0);
    v_texCoords = a_texCoord;
    v_color = a_color;
    v_tilingFactor = a_tilingFactor;
}

