#version 460 core

in vec3 vPosition;
in vec3 vNormal;
in vec3 vColor;
in vec2 vTexcoord;

out vec4 fColor;

uniform float time;
uniform float u[32];

layout (binding = 0) uniform sampler2D fbColor;
layout (binding = 1) uniform sampler2D fbDepth;
layout (binding = 2) uniform sampler2D fbPosition;
layout (binding = 3) uniform sampler2D fbNormal;

void main() {
    fColor = texture(fbColor, vTexcoord);
}
