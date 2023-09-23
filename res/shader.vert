#version 460 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;

layout (location = 0) out vec4 vPosition;
layout (location = 1) out vec4 vColor;

layout (location = 0) uniform mat4 uModel;
layout (location = 1) uniform mat4 uView;
layout (location = 2) uniform mat4 uProjection;

void main() {
	vPosition = uProjection * uView * uModel * vec4(aPosition, 1.0);
	vColor = vec4(aColor, 1.0);

	gl_Position = vPosition;
}
