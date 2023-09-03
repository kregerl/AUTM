#version 460 core
layout (location = 0) in vec3 a_world_position;
layout (location = 1) in vec3 a_local_position;
layout (location = 2) in vec4 a_color;
layout (location = 3) in vec2 a_texture_coordinate;
layout (location = 4) in float a_texture_index;
layout (location = 5) in float a_tiling_factor;
layout (location = 6) in float a_thickness;
layout (location = 7) in float a_fade;

layout (std140, binding = 0) uniform camera {
    mat4 u_view_projection_matrix;
};

layout (location = 0) out vec3 v_local_position;
layout (location = 1) out vec4 v_color;
layout (location = 2) out vec2 v_texture_coordinate;
layout (location = 3) out float v_texture_index;
layout (location = 4) out float v_tiling_factor;
layout (location = 5) out float v_thickness;
layout (location = 6) out float v_fade;

void main() {
    gl_Position = u_view_projection_matrix * vec4(a_world_position, 1.0f);
    v_local_position = a_local_position;
    v_color = a_color;
    v_texture_index = a_texture_index;
    v_tiling_factor = a_tiling_factor;
    v_texture_coordinate = a_texture_coordinate;
    v_thickness = a_thickness;
    v_fade= a_fade;
}
