#version 460 core

layout (location = 0) in vec2 v_texture_coordinate;
layout (location = 0) out vec4 o_color;

layout (binding = 0) uniform sampler2D u_texture;
uniform vec3 u_color;
uniform vec3 u_background_color;

void main() {
    vec4 color = texture(u_texture, v_texture_coordinate) * vec4(u_color, 1.0f);
    if (color.rgb == vec3(0.0f)) {
        color = vec4(u_background_color, 1.0f);
    }
    o_color = color;
}
