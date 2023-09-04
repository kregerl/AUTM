#version 460 core

#define LIVING vec4(1.0f)
#define DEAD vec4(0.0f)
layout (location = 0) out vec4 o_color;

layout (location = 0) in vec2 v_texture_coordinate;

uniform vec2 u_resolution;
uniform sampler2D u_texture;

void main() {
    vec2 uv = gl_FragCoord.xy / u_resolution.xy;

    vec3 color = vec3(0.0);
    float neighbors = 0.0;

    for (float i = -1.0; i <= 1.0; i += 1.0)
    {
        for (float j = -1.0; j <= 1.0; j += 1.0)
        {
            vec2 offset = vec2(i, j) / u_resolution.xy;
            vec4 lookup = texture(u_texture, uv + offset);
            neighbors += lookup.r;
        }
    }

    float cell = texture(u_texture, uv).x;

    if (cell > 0.0) {
        if (neighbors >= 3.0 && neighbors <= 4.0) {
            color = vec3(1.0);
        }
    } else if (neighbors > 2.0 && neighbors < 4.0) {
        color = vec3(1.0);
    }

    o_color = vec4(color, 1.0f);
}
