#version 460 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec4 a_color;

layout (std140, binding = 0) uniform camera {
    mat4 u_view_projection_matrix;
};

layout (location = 0) out vec4 v_color;

void main() {
    gl_Position = u_view_projection_matrix * vec4(a_position, 1.0f);
    v_color = a_color;
}
