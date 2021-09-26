#version 460 core
layout (location = 0) out vec4 fragColor;

in vec2 v_texCoords;

void main() {
    FragColor = vec4(v_texCoords, 0.0, 1.0);
}

