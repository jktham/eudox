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
uniform vec3 viewPos;
uniform mat4 uiProjection;
uniform float u[32];

layout (binding = 0) uniform sampler2D fbColor;
layout (binding = 1) uniform sampler2D fbDepth;
layout (binding = 2) uniform sampler2D fbPosition;
layout (binding = 3) uniform sampler2D fbNormal;

void main() {
    fColor = texture(fbColor, vTexcoord);
}
