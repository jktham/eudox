#version 460 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexcoord;

layout (location = 0) out vec4 vPosition;
layout (location = 1) out vec3 vNormal;
layout (location = 2) out vec3 vColor;
layout (location = 3) out vec2 vTexcoord;

layout (location = 0) uniform mat4 model;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 projection;
layout (location = 3) uniform float time;
layout (location = 4) uniform vec2 resolution;

void main() {
	vPosition = projection * view * model * vec4(aPosition, 1.0);
	vNormal = mat3(transpose(inverse(model))) * aNormal;
	vColor = aColor;
	vTexcoord = aTexcoord;

	gl_Position = vPosition;
}
