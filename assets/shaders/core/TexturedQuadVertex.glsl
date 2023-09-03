#version 460 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texture_coordinate;
layout(location = 3) in float a_texture_index;
layout(location = 4) in float a_tiling_factor;

layout (std140, binding = 0) uniform camera {
    mat4 u_view_projection_matrix;
};

layout (location = 0) out vec4 v_color;
layout (location = 1) out vec2 v_texture_coordinate;
layout (location = 2) out float v_texture_index;
layout (location = 3) out float v_tiling_factor;

void main() {
    gl_Position = u_view_projection_matrix * vec4(a_position, 1.0f);
    v_color = a_color;
    v_texture_coordinate = a_texture_coordinate;
    v_texture_index = a_texture_index;
    v_tiling_factor = a_tiling_factor;
}
