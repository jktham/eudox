#version 460 core

in vec4 vPosition;
in vec3 vNormal;
in vec3 vColor;
in vec2 vTexcoord;

out vec4 fColor;

void main() {
	fColor = vec4(vColor, 1.0);
}
