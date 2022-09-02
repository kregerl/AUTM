#version 460 core
layout (location = 0) out vec4 fragColor;
layout (binding = 0) uniform sampler2D u_texture;

in vec2 v_texCoords;
in vec3 v_color;
in float v_tilingFactor;
in vec2 v_fCoord;

uniform vec3 u_center;
uniform vec2 u_resolution;
uniform float u_iterations;

float mandelbrot(vec2 uv) {
    vec2 c = uv;
    vec2 z = vec2(0.0);
    float iter = 0.0;
    for (float i = 0; i < u_iterations; i++) {
        z = vec2(
        pow(z.x, 2) - pow(z.y, 2),
        2.0 * z.x * z.y) + c;
        if (dot(z, z) > 4.0)
        return iter / u_iterations;
        iter++;
    }
    return 0.0;
}

void main() {
    vec2 p = {
    (gl_FragCoord.x - 0.5 * u_resolution.x) * (4 / u_resolution.x) * (u_resolution.x / (u_resolution.y*u_center.z)) + u_center.x,
    (gl_FragCoord.y - 0.5 * u_resolution.y) * (4 / u_resolution.y) * (1 / u_center.z) + u_center.y
    };

    float shade = mandelbrot(p);
    fragColor = vec4(vec3(shade), 1.0);
}

