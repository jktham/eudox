#version 460 core

in vec3 aPosition;
in vec3 aNormal;
in vec3 aColor;
in vec2 aTexcoord;

out VS_OUT {
	vec3 vPosition;
	vec3 vNormal;
	vec3 vColor;
	vec2 vTexcoord;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;
uniform vec2 resolution;
uniform vec3 color;
uniform vec3 viewPos;
uniform mat4 uiProjection;
uniform float u[32];

void main() {
	vs_out.vPosition = vec3(model * vec4(aPosition, 1.0));
	vs_out.vNormal = mat3(transpose(inverse(model))) * aNormal;
	vs_out.vColor = aColor * color;
	vs_out.vTexcoord = aTexcoord;

	gl_Position = projection * view * model * vec4(aPosition, 1.0);
}
