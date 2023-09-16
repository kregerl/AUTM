#version 460 core
// Inspired from the paper https://arxiv.org/pdf/1111.1567.pdf

#define PI 3.14159265359f

layout (location = 0) out vec4 o_color;

layout (location = 0) in vec2 v_texture_coordinate;

uniform vec2 u_radius;
uniform float u_delta_time;

// SmoothLife rules
uniform float u_b1 = 0.257;
uniform float u_b2 = 0.336;
uniform float u_d1 = 0.365;
uniform float u_d2 = 0.549;

uniform float u_alpha_n = 0.028;
uniform float u_alpha_m = 0.147;

uniform bool u_regenerate;
uniform vec2 u_resolution;
uniform sampler2D u_texture;

//// SmoothLife rules
//const float u_b1 = 0.257;
//const float u_b2 = 0.336;
//const float u_d1 = 0.365;
//const float u_d2 = 0.549;
//
//const float u_alpha_n = 0.028;
//const float u_alpha_m = 0.147;

float sigmoid_a(float x, float a, float b) {
    return 1.0f / (1.0f + exp(-(x - a) * 4.0f / b));
}

float sigmoid_b(float x, float b, float eb) {
    return 1.0f - sigmoid_a(x, b, eb);
}

float sigmoid_ab(float x, float a, float b, float ea, float eb) {
    return sigmoid_a(x, a, ea) * sigmoid_b(x, b, eb);
}

float sigmoid_mix(float x, float y, float m, float em) {
    return x * (1.0f - sigmoid_a(m, 0.5f, em)) + y * sigmoid_a(m, 0.5f, em);
}

float s(vec2 disk_ring) {
    return sigmoid_mix(sigmoid_ab(disk_ring.x, u_b1, u_b2, u_alpha_n, u_alpha_n),
    sigmoid_ab(disk_ring.x, u_d1, u_d2, u_alpha_n, u_alpha_n), disk_ring.y, u_alpha_m
    );
}

float ramp_step(float steppos, float t) {
    return clamp(t - steppos + 0.5f, 0.0f, 1.0f);
}

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898f, 78.233f))) * 43758.5453f);
}

void main() {
    if (u_regenerate) {
        float color = rand(gl_FragCoord.xy);
        o_color = vec4(color, color, color, 1.0f);
        return;
    }

    vec2 uv = gl_FragCoord.xy / u_resolution;

    vec2 area = PI * u_radius * u_radius;
    area.x -= area.y;

    vec3 color = texture(u_texture, uv).xyz;

    vec2 result = vec2(0.0f);
    for (float dx = -u_radius.x; dx <= u_radius.x; dx++) {
        for (float dy = -u_radius.x; dy <= u_radius.x; dy++) {
            vec2 d = vec2(dx, dy);
            float dist = length(d);
            vec2 offset = d / u_resolution.xy;
            vec2 samplepos = fract(uv + offset);
            float weight = texture(u_texture, samplepos).x;
            result.x += weight * ramp_step(u_radius.y, dist) * (1.0f - ramp_step(u_radius.x, dist));

            result.y += weight * (1.0f - ramp_step(u_radius.y, dist));
        }
    }

    vec2 normalized_result = result / area;
    color = vec3(color.x + u_delta_time * (2.0f * s(normalized_result) - 1.0f));
    color = clamp(color, 0.0f, 1.0f);

    o_color = vec4(color, 1.0f);
}