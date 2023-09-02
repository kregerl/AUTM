#version 460 core
layout (location = 0) out vec4 fragColor;

uniform vec2 u_resolution;
uniform float u_time;
uniform vec3 u_camera;

/*
* p - Point
* c - Center point of sphere
* r - Radius of the sphere
*/
float sphereSDF(vec3 p, vec3 c, float r) {
    return length(p - c) - r;
}

/*
* p - Point
* r - Radius of circle vec2(inner, outer)
*/
float torusSDF(vec3 p, vec2 r) {
    float x = length(p.xz) - r.x;
    return length(vec2(x, p.y)) - r.y;
}

/*
* p - Point
* a - Start center point of the capsule
* b - End center point of the capsule
* r - Radius of the capsule ends (ends are just two circles)
*/
float capsuleSDF(vec3 p, vec3 a, vec3 b, float r) {
    vec3 ab = b - a;
    vec3 ap = p - a;

    float t = dot(ab, ap) / dot(ab, ab);
    t = clamp(t, 0.0, 1.0);

    vec3 c = a + t*ab;
    return length(p - c) - r;
}

/*
* p - Point
* s - Size of the cube (Half og the width, height and depth)
*/
float cubeSDF(vec3 p, vec3 s) {
    return length(max(abs(p) - s, 0.0));
}

float unionSDF(float sdf1, float sdf2) {
    return min(sdf1, sdf2);
}

float smoothMin(float a, float b, float k) {
    float h = clamp(0.5 + 0.5*(b-a)/k, 0.0, 1.0);
    return mix(b, a, h) - k*h*(1.0-h);
}

mat2 rotate(float angle) {
    float s = sin(angle);
    float c = cos(angle);
    return mat2(c, -s, s, c);
}

float sceneSDF(vec3 point) {
    vec3 p = point;
    float pd = point.y;

    // Sphere 1
    vec3 c0 = vec3(0.5, 1.75, 1.0);
    float s0 = sphereSDF(point, c0, 0.25);

    // Sphere 1
    vec3 c1 = vec3(1.25, 1.0, 0.0);
    float s1 = sphereSDF(point, c1, 1.0);

    // Torus
    point.yz *= rotate(.45);
    float s2 = torusSDF(point, vec2(0.65, 0.25));
    point = p;

    float smthAmt = 0.4;

    point.xz *= rotate(0.5);
    point.yz *= rotate(0.2);
    float cSDF = cubeSDF(point + vec3(1.5, 1.0, 1.0), vec3(0.5));
    point = p;

    float capsule = capsuleSDF(point, vec3(0, 0.0, 1.0), vec3(1.0, 1.5, 1.0), .3);
    float smth0 = smoothMin(s0, capsule, smthAmt);
    float smth1 = smoothMin(smth0, s2, smthAmt);
    return smth1;
}

vec3 calculateNormal(vec3 point) {
    const vec3 step = vec3(0.001, 0.0, 0.0);

    float x = sceneSDF(point + step.xyy) - sceneSDF(point - step.xyy);
    float y = sceneSDF(point + step.yxy) - sceneSDF(point - step.yxy);
    float z = sceneSDF(point + step.yyx) - sceneSDF(point - step.yyx);

    vec3 normal = vec3(x, y, z);
    return normalize(normal);
}

vec3 rayMarch(vec3 rayOrigin, vec3 rayDirection) {
    float dst = 0.0;

    // TODO: Make these uniforms and controllable by ImGui.
    const int STEPS = 32;
    const float MIN_HIT_DST = 0.001;
    const float MAX_DST = 1000.0;

    for (int i = 0; i < STEPS; i++) {
        vec3 currentPos = rayOrigin + dst * rayDirection;

        float dstToScene = sceneSDF(currentPos);
        if (dstToScene < MIN_HIT_DST) {
            vec3 normal = calculateNormal(currentPos);

            return normal * 0.5 + 0.5;
        }
        if (dst > MAX_DST) {
            break;
        }
        dst += dstToScene;

    }

    return vec3(0.0);
}

void main() {
    vec2 uv = gl_FragCoord.xy / u_resolution.xy;
    uv -= 0.5;
    uv.x *= u_resolution.x / u_resolution.y;

    vec3 camera = vec3(0.0, 0.0, -10.0);
    vec3 rd = vec3(uv, 1.0);

    vec3 color = rayMarch(camera, rd);

    fragColor = vec4(color, 1.0);
}
