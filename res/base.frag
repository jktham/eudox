#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec3 vColor;
layout (location = 3) in vec2 vTexcoord;

layout (location = 0) out vec4 fColor;

void main() {
	fColor = vec4(vColor, 1.0);
}
