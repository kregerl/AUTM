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
        return iter;
        //            return iter / u_iterations;
        iter++;
    }
    return 0.0;
}

vec3 color(int r, int g, int b) {
    return vec3(float(r) / 255.0, float(g) / 255.0, float(b) / 255.0);
}

vec3[16] palette = { color(66, 30, 15), color(25, 7, 26), color(9, 1, 47), color(4, 4, 73), color(0, 7, 100), color(12, 44, 138), color(24, 82, 177), color(57, 125, 209),
color(134, 181, 229), color(211, 236, 248), color(241, 233, 191), color(248, 201, 95), color(255, 170, 0), color(204, 128, 0), color(153, 87, 0), color(106, 52, 3) };

void main() {
    vec2 st = gl_FragCoord.xy / u_resolution.xy;
    vec2 p = {
        (gl_FragCoord.x - 0.5 * u_resolution.x) * (4 / u_resolution.x) * (u_resolution.x / (u_resolution.y*u_center.z)) + u_center.x,
        (gl_FragCoord.y - 0.5 * u_resolution.y) * (4 / u_resolution.y) * (1 / u_center.z) + u_center.y
    };

    float shade = mandelbrot(p);
    vec3 color;
    if (shade < u_iterations && shade > 0) {
        int i = int(floor(shade)) % 16;
        vec3 c1 = palette[i];
        vec3 c2 = palette[i + 1];
        color = mix(c1, c2, st.x);
    }
    fragColor = vec4(color, 1.0);
}

