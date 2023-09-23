#version 460 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;

layout (location = 0) out vec4 vPosition;
layout (location = 1) out vec4 vColor;

layout (location = 0) uniform mat4 mvp;

void main() {
	vPosition = mvp * vec4(aPosition, 1.0);
	vColor = vec4(aColor, 1.0);

	gl_Position = vPosition;
}
