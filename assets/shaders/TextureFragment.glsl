#version 460 core
layout (location = 0) out vec4 fragColor;

layout (binding = 0) uniform sampler2D u_texture;

in vec2 v_texCoords;
in vec3 v_color;
in float v_tilingFactor;

void main() {
    fragColor = texture(u_texture, v_texCoords * v_tilingFactor) * vec4(v_color, 0.1);
}

