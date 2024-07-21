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
uniform float u[32];

layout (binding = 0) uniform sampler2D texture0;
layout (binding = 1) uniform sampler2D texture1;

float luminance(vec3 color) {
    return dot(color, vec3(0.299, 0.587, 0.114));
}

void main() {
    float scale = u[0] != 0 ? u[0] : 16.0;
    float stages = u[1] != 0 ? u[1] : 8.0;

	vec2 xy = floor(vTexcoord * resolution / scale) * scale;
    float avg = 0.0;
    for (int i = 0; i < scale; i++) {
        for (int j = 0; j < scale; j++) {
            avg += luminance(texture(texture0, (xy + vec2(i, j)) / resolution).rgb) / (scale * scale);
        }
    }

    float cell = floor(clamp(avg, 0.0, 0.999) * stages) / stages;
    vec2 cellOffset = mod(vTexcoord * resolution, scale) / vec2(scale*stages, scale);

    fColor = texture(texture1, vec2(cell, 0.0) + cellOffset);
}
