#version 460 core

in vec3 vPosition;
in vec3 vNormal;
in vec3 vColor;
in vec2 vTexcoord;

layout (location = 0) out vec4 fColor;
layout (location = 1) out vec3 fPosition;
layout (location = 2) out vec3 fNormal;

layout (binding = 0) uniform sampler2D texture0;
layout (binding = 1) uniform sampler2D texture1;

void main() {
	fColor = vec4(vColor, 1.0) * texture(texture0, vTexcoord.st);
	fPosition = vPosition;
	fNormal = normalize(vNormal);
}
