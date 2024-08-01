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

uniform float sonarSpeed = 40.0;
uniform float sonarDelay = 3.0;
uniform float sonarSize = 8.0;

void main() {
    float dist = distance(viewPos, texture(texture1, vTexcoord).xyz);
    float d = 1 - clamp(abs(mod(time*sonarSpeed, sonarSpeed*sonarDelay) - dist), 0, sonarSize) / sonarSize;
    fColor = vec4(d * vec3(texture(texture0, vTexcoord)), 1.0);
}
