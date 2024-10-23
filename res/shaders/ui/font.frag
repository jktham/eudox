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
uniform mat4 inverseView;
uniform float fov;
uniform uvec3 mask;

layout (binding = 0) uniform sampler2D texture0;
layout (binding = 1) uniform sampler2D texture1;

uniform vec3 color = vec3(1.0, 1.0, 1.0);

void main() {
	vec4 font = texture(texture0, vTexcoord.st);
	font.a = font.r;
	font.rgb = color;
	if (font.a < 0.5) discard;

	fColor = vec4(vColor, 1.0) * font;
}
