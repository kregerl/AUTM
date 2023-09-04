#version 460 core

layout (location = 0) in vec2 v_texture_coordinate;
layout (location = 0) out vec4 o_color;

layout (binding = 0) uniform sampler2D u_texture;

void main() {
    o_color = texture(u_texture, v_texture_coordinate);
}
