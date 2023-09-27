#version 460 core

in vec3 aPosition;
in vec3 aNormal;
in vec3 aColor;
in vec2 aTexcoord;

out vec4 vPosition;
out vec3 vNormal;
out vec3 vColor;
out vec2 vTexcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;
uniform vec2 resolution;
uniform vec3 color;

void main() {
	vPosition = projection * view * model * vec4(aPosition, 1.0);
	vNormal = mat3(transpose(inverse(model))) * aNormal;
	vColor = aColor * color;
	vTexcoord = aTexcoord;

	gl_Position = vPosition;
}
