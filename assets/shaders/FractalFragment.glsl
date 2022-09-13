#version 460 core
layout (location = 0) out vec4 fragColor;
layout (binding = 0) uniform sampler2D u_texture;

in vec2 v_texCoords;
in vec3 v_color;
in float v_tilingFactor;
in vec2 v_fCoord;

// x, y are center z is zoom
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
        if (dot(z, z) > 4.0) {
            return iter;
            //            return iter / u_iterations;
        }
        iter++;
    }
    return 0.0;
}

float smth(float iter, vec2 z) {
    float sl = iter - log2(log2(dot(z, z))) + 4.0;

    float al = smoothstep(-0.1, 0.0, sin(0.5*6.2831));
    iter = mix(iter, sl, al);

    return iter;
}

float smoothMandelbrot(vec2 uv) {
    vec2 c = uv;
    vec2 z = vec2(0.0);
    float iter = 0.0;
    for (float i = 0; i < u_iterations; i++) {
        z = vec2(
        pow(z.x, 2) - pow(z.y, 2),
        2.0 * z.x * z.y) + c;
        if (dot(z, z) > 4.0) {
            return smth(iter, z);
            //            return iter / u_iterations;
        }
        iter++;
    }
    return 0.0;
}

vec2 cmul(vec2 a, vec2 b) { return vec2(a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x); }

float mandelbrot_perturbation(vec2 c, vec2 dc) {
    vec2 z  = vec2(0.0);
    vec2 dz = vec2(0.0);
    float n = -1.0;
    for (int i=0; i<4000; i++)
    {
        dz = cmul(2.0*z+dz, dz) + dc;// dz = cmul(dz,dz)+dc + 2.0*cmul(z,dz);

        z  = cmul(z, z)+c;// this could be precomputed since it's constant for the whole image

        // instead of checking for Wn to escape...
        // if( dot(z+dz,z+dz)>4.0 ) { n=float(i); break; }
        // ... we only check ΔZn, since Zn is periodic and can't escape
        if (dot(dz, dz)>4.0) { n=float(i); break; }
    }
    return n;
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


    // Mandelbrot Perturbation
    //    float zoom = 1.5 * (1 / u_center.z);
    //    vec2 c = vec2(-1.1900443,0.3043895);
    //    vec3 color = vec3(0.0);
    //    float m = mandelbrot_perturbation(c, p);
    //
    //    color += (m<0.0) ? vec3(0.0) : 0.5 + 0.5*cos( pow(zoom,0.22)*m*0.05 + vec3(3.0,3.5,4.0));
    //    fragColor = vec4(color, 1.0);


    // Smooth Color Mandebrot
    //    float shade = smoothMandelbrot(p);
    //
    //    vec3 color = 0.5 + 0.5*cos(3.0 + shade*0.15 + vec3(0.0, 0.6, 1.0));
    //    fragColor = vec4(color, 1.0);


    // Normal Mandelbrot
    float shade = mandelbrot(p);
    vec3 color;
    if (shade < u_iterations && shade > 0) {
        int i = int(floor(shade)) % 16;
        vec3 c1 = palette[i];
        vec3 c2 = palette[i + 1];
        color = mix(c1, c2, 0.5);
    }
    fragColor = vec4(color, 1.0);

}

