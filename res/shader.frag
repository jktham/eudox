#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

layout (location = 0) out vec4 fColor;

void main() {
	fColor = vColor;
}
