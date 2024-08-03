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
uniform vec3 viewPos;
uniform mat4 uiProjection;
uniform float u[32];

layout (binding = 0) uniform sampler2D fbColor;
layout (binding = 1) uniform sampler2D fbDepth;
layout (binding = 2) uniform sampler2D fbPosition;
layout (binding = 3) uniform sampler2D fbNormal;

uniform vec3 edgeColor = vec3(0.0, 0.0, 0.0);
uniform float edgeWidth = 1.0;

void main() {
    float offsetx = 1.0 / resolution.x * edgeWidth;
    float offsety = 1.0 / resolution.y * edgeWidth;

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
        -1.0f, -1.0f, -1.0f,
        -1.0f,  8.0f, -1.0f,
        -1.0f, -1.0f, -1.0f
    );
    
    vec3 sampleNormal[9];
    for(int i = 0; i < 9; i++) {
        sampleNormal[i] = vec3(texture(fbNormal, vTexcoord.st + offsets[i]));
    }
    vec3 sampleDepth[9];
    for(int i = 0; i < 9; i++) {
        sampleDepth[i] = vec3(texture(fbDepth, vTexcoord.st + offsets[i]));
    }
    vec3 samplePosition[9];
    for(int i = 0; i < 9; i++) {
        samplePosition[i] = vec3(texture(fbPosition, vTexcoord.st + offsets[i]));
    }

    vec3 edgeNormal = vec3(0.0);
    vec3 edgeDepth = vec3(0.0);
    vec3 edgePosition = vec3(0.0);
    for(int i = 0; i < 9; i++) {
        edgeNormal += sampleNormal[i] * kernel[i];
        edgeDepth += sampleDepth[i] * kernel[i];
        edgePosition += samplePosition[i] * kernel[i];
    }

    vec3 viewDir = normalize(viewPos - vec3(texture(fbPosition, vTexcoord.st)));
    float angle = abs(dot(vec3(texture(fbNormal, vTexcoord.st)), viewDir));

    vec3 col = vec3(texture(fbColor, vTexcoord.st));
    if (length(edgeNormal) > 0.1 || length(edgeDepth) > 0.8 || length(edgePosition) > 0.4) {
        fColor = vec4(col * edgeColor, 1.0);
    } else {
        fColor = vec4(col, 1.0);
    }
    
}
