#version 460 core
layout (location = 0) out vec4 fragColor;

uniform vec2 u_resolution;

float sphereSDF(vec3 point, vec3 center, float radius) {
    return length(point - center) - radius;
}

float unionSDF(float sdf1, float sdf2) {
    return min(sdf1, sdf2);
}

float sceneSDF(vec3 point) {
    vec3 c0 = vec3(0.0);
    float s0 = sphereSDF(point, c0, 1.0);

    vec3 c1 = vec3(4.0, 0.0, 0.0);
    float s1 = sphereSDF(point, c1, 1.0);

    return unionSDF(s0, s1);
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
