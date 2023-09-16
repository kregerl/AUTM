#version 460 core
layout (location = 0) in vec3 a_pos;

layout (std140, binding = 0) uniform camera {
    mat4 u_view_projection_matrix;
};

void main() {
    gl_Position = u_view_projection_matrix * vec4(a_pos, 1.0);
}
