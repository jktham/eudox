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

void main() {
    const float SPEED = 40;
    const float DELAY = 4;
    const float SIZE = 8;

    float dist = distance(viewPos, texture(texture1, vTexcoord).xyz);
    float d = 1 - clamp(abs(mod(time*SPEED, SPEED*DELAY) - dist), 0, SIZE) / SIZE;
    fColor = vec4(d * vec3(texture(texture0, vTexcoord)), 1.0);
}
