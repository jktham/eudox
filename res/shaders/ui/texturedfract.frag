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

void main() {
	if (texture(texture0, vTexcoord.st).a < 0.5) discard;
	fColor = vec4(fract(max(abs(vec3(vec4(vColor, 1.0) * texture(texture0, vTexcoord.st))) - 0.000001, 0.0)), 1.0);
}
