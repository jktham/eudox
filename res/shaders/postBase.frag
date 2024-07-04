#version 460 core

in vec3 vPosition;
in vec2 vTexcoord;

out vec4 fColor;

uniform float time;
uniform float u[32];

layout (binding = 0) uniform sampler2D colorTexture;
layout (binding = 1) uniform sampler2D depthTexture;

void main() {
    fColor = texture(colorTexture, vTexcoord);
}
