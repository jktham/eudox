#version 460 core

in vec4 vPosition;
in vec2 vTexcoord;

out vec4 fColor;

uniform float time;
uniform float u[32];

layout (binding = 0) uniform sampler2D colorTexture;
layout (binding = 1) uniform sampler2D depthTexture;

const float offset = 1.0 / 600.0;

void main() {
    vec2 offsets[9] = vec2[] (
        vec2(-offset, offset),
        vec2(0.0, offset),
        vec2(offset, offset),
        vec2(-offset, 0.0),
        vec2(0.0, 0.0),
        vec2(offset, 0.0),
        vec2(-offset, -offset),
        vec2(0.0, -offset),
        vec2(offset, -offset)
    );

    // float kernel[9] = float[] (
    //     1.0/16, 2.0/16, 1.0/16,
    //     2.0/16, 4.0/16, 2.0/16,
    //     1.0/16, 2.0/16, 1.0/16
    // );

    float kernel[9] = float[] (
        u[0], u[1], u[2],
        u[3], u[4], u[5],
        u[6], u[7], u[8]
    );
    
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++) {
        sampleTex[i] = vec3(texture(colorTexture, vTexcoord.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++) {
        col += sampleTex[i] * kernel[i];
    }
    
    fColor = vec4(col, 1.0);
}
