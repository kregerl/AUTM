#version 460 core
layout (location = 0) out vec4 fragColor;

in vec4 v_color;

void main() {
    fragColor = vec4(v_color);
}

