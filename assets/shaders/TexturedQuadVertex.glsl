#version 460 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_textureCoordinate;
layout(location = 3) in float a_textureIndex;
layout(location = 4) in float a_tilingFactor;

layout (std140, binding = 0) uniform camera {
    mat4 u_viewProjectionMatrix;
};

layout (location = 0) out vec4 v_color;
layout (location = 1) out vec2 v_textureCoordinate;
layout (location = 2) out float v_textureIndex;
layout (location = 3) out float v_tilingFactor;

void main() {
    gl_Position = u_viewProjectionMatrix * vec4(a_position, 1.0f);
    v_color = a_color;
    v_textureCoordinate = a_textureCoordinate;
    v_textureIndex = a_textureIndex;
    v_tilingFactor = a_tilingFactor;
}
