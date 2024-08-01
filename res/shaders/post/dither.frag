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

layout (binding = 0) uniform sampler2D texture0;
layout (binding = 1) uniform sampler2D texture1;

uniform float ditherScale = 16.0;
uniform float ditherStages = 8.0;
uniform float ditherSamples = 4.0;

float luminance(vec3 color) {
    return dot(color, vec3(0.299, 0.587, 0.114));
}

void main() {
	vec2 xy = floor(vTexcoord * resolution / ditherScale) * ditherScale;
    float avg = 0.0;
    float k = 0.0;
    for (int i = 0; i < ditherScale; i += int(ditherScale / ditherSamples)) {
        for (int j = 0; j < ditherScale; j += int(ditherScale / ditherSamples)) {
            avg += luminance(texture(texture0, (xy + vec2(i, j)) / resolution).rgb);
            k++;
        }
    }
    avg = avg / k;

    float cell = floor(clamp(avg, 0.0, 0.999) * ditherStages) / ditherStages;
    vec2 cellOffset = mod(vTexcoord * resolution, ditherScale) / vec2(ditherScale*ditherStages, ditherScale);

    fColor = texture(texture1, vec2(cell, 0.0) + cellOffset);
}
