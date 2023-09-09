#version 460 core

layout (location = 0) out vec4 o_color;

layout (location = 0) in vec2 v_texture_coordinate;

uniform int u_rule;
uniform uint u_frame;
uniform bool u_regenerate;
uniform vec2 u_resolution;
uniform sampler2D u_texture;

void main() {
    if (u_regenerate) {
        o_color = vec4(0.0f);
        return;
    }

    if (gl_FragCoord.y > u_resolution.y - 1.0){
        if (int(gl_FragCoord.x) == int(u_resolution.x / 2.0f)) {
            o_color = vec4(1.0);
        } else {
            o_color = vec4(0.0);
        }
    } else {
        ivec2 texture_size = textureSize(u_texture, 0);

        float left = texture(u_texture, (gl_FragCoord.xy + vec2(-1, 1) + (u_frame < texture_size.y ? ivec2(0, 0) : ivec2(0, -1))) / u_resolution.xy).x;
        float center = texture(u_texture, (gl_FragCoord.xy + vec2(0, 1) + (u_frame < texture_size.y ? ivec2(0, 0) : ivec2(0, -1))) / u_resolution.xy).x;
        float right = texture(u_texture, (gl_FragCoord.xy + vec2(1, 1) + (u_frame < texture_size.y ? ivec2(0, 0) : ivec2(0, -1))) / u_resolution.xy).x;

        int rule_case = int(4.0 * left + 2.0 * center + right);

        if (pow(2.0, float(rule_case)) <= mod(float(u_rule), pow(2.0, float(rule_case) + 1.0))){
            o_color = vec4(1.0);
        } else {
            o_color = vec4(0.0);
        }
    }
}
