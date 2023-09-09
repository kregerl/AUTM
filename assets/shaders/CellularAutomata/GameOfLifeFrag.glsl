#version 460 core

#define LIVING 1.0f

layout (location = 0) out vec4 o_color;

layout (location = 0) in vec2 v_texture_coordinate;

uniform bool u_regenerate;
uniform float u_board_size;
uniform vec2 u_resolution;
uniform sampler2D u_texture;

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void main() {
    if (u_regenerate) {
        float color = rand(gl_FragCoord.xy);
        o_color = vec4(color, color, color, 1.0f);
        return;
    }

    vec2 aspect_ratio = vec2(u_resolution.x / u_resolution.y, 1.0f);
    vec2 board_size = vec2(u_board_size);
    if (u_board_size == 0.0f) {
        board_size = vec2(min(u_resolution.x, u_resolution.y));
    }
    board_size = floor(aspect_ratio * board_size);
    vec2 pixel_size = 1.0f / board_size;
    vec2 uv = floor(board_size * v_texture_coordinate) / board_size + 0.5f * pixel_size;

    vec3 color = vec3(0.0);
    float neighbors = 0.0;

    for (float i = -1.0; i <= 1.0; i += 1.0)
    {
        for (float j = -1.0; j <= 1.0; j += 1.0)
        {
            vec2 offset = vec2(i, j) * pixel_size;
            vec4 lookup = texture(u_texture, uv + offset);
            neighbors += lookup.r;
        }
    }

    float cell = texture(u_texture, uv).x;

    if (cell == LIVING) {
        if (neighbors >= 3.0 && neighbors <= 4.0) {
            color = vec3(1.0);
        }
    } else if (neighbors > 2.0 && neighbors < 4.0) {
        color = vec3(1.0);
    }

    o_color = vec4(color, 1.0f);
}
