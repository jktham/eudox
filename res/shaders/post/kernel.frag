#version 460 core

in vec3 vPosition;
in vec3 vNormal;
in vec3 vColor;
in vec2 vTexcoord;

out vec4 fColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;
uniform vec2 resolution;
uniform vec3 color;
uniform vec3 light;
uniform vec3 viewPos;
uniform mat4 uiProjection;
uniform float u[32]; // kernel[9]

layout (binding = 0) uniform sampler2D texture0;
layout (binding = 1) uniform sampler2D texture1;

void main() {
    float offsetx = 1.0 / resolution.x * 1.0;
    float offsety = 1.0 / resolution.y * 1.0;

    vec2 offsets[9] = vec2[] (
        vec2(-offsetx, offsety),
        vec2(0.0, offsety),
        vec2(offsetx, offsety),
        vec2(-offsetx, 0.0),
        vec2(0.0, 0.0),
        vec2(offsetx, 0.0),
        vec2(-offsetx, -offsety),
        vec2(0.0, -offsety),
        vec2(offsetx, -offsety)
    );

    float kernel[9] = float[] (
        u[0], u[1], u[2],
        u[3], u[4], u[5],
        u[6], u[7], u[8]
    );
    
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++) {
        sampleTex[i] = vec3(texture(texture0, vTexcoord.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++) {
        col += sampleTex[i] * kernel[i];
    }
    
    fColor = vec4(col, 1.0);
}
