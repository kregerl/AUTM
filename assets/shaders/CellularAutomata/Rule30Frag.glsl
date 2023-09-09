#version 460 core

layout (location = 0) out vec4 o_color;

layout (location = 0) in vec2 v_texture_coordinate;
uniform bool u_regenerate;
uniform vec2 u_resolution;

uniform sampler2D u_texture;

void main() {
//    https://www.shadertoy.com/view/msfGWX
//    Some weird issue with resolution
    //    int rule = 30;// rule between 0 and 255
    //    float density = 0.01;// determines initial density of starting row
    //
    //    vec2 seed = vec2(0.2, 0.5);
    //
    //    if (gl_FragCoord.y > u_resolution.y - 1.0){
    //        if (int(gl_FragCoord.x) == int(u_resolution.x / 2.0f)) {
    //            o_color = vec4(0.0);
    //        } else {
    //            o_color = vec4(1.0);
    //        }
    //    }
    //    else {
    //        float leftPix = texture(u_texture, (gl_FragCoord.xy + vec2(-1, 1))/u_resolution.xy).x;
    //        float centPix = texture(u_texture, (gl_FragCoord.xy + vec2(0, 1))/u_resolution.xy).x;
    //        float righPix = texture(u_texture, (gl_FragCoord.xy + vec2(1, 1))/u_resolution.xy).x;
    //
    //        int ruleCase = int(4.0 * leftPix + 2.0 * centPix + righPix);
    //
    //        if (pow(2.0, float(ruleCase)) <= mod(float(rule), pow(2.0, float(ruleCase) + 1.0))){
    //            o_color = vec4(1.0);
    //        }
    //        else {
    //            o_color = vec4(0.0);
    //        }
    //    }

}
