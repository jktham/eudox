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
    float scale = u[0] != 0 ? u[0] : 8.0;

	vec2 xy = floor(vTexcoord * resolution / scale) / resolution * scale;
    fColor = texture(texture0, xy);
}
