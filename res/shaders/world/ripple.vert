#version 460 core

in vec3 aPosition;
in vec3 aNormal;
in vec3 aColor;
in vec2 aTexcoord;

#ifdef HASGEOMSTAGE
out VS_OUT {
	vec3 vPosition;
	vec3 vNormal;
	vec3 vColor;
	vec2 vTexcoord;
} vs_out;
#define vPosition vs_out.vPosition
#define vNormal vs_out.vNormal
#define vColor vs_out.vColor
#define vTexcoord vs_out.vTexcoord
#else
out vec3 vPosition;
out vec3 vNormal;
out vec3 vColor;
out vec2 vTexcoord;
#endif

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;
uniform vec2 resolution;
uniform vec3 color;
uniform vec3 light;
uniform vec3 viewPos;
uniform mat4 uiProjection;
uniform float u[32];

void main() {
	vPosition = vec3(model * vec4(aPosition, 1.0));
	vNormal = mat3(transpose(inverse(model))) * aNormal;
	vColor = aColor * color;
	vTexcoord = aTexcoord;

	float timeFactor = 8.0;
	float posFactor = 8.0;
	float exponent = 1.0;
	float height = 0.05;
	float ripple = height * pow((sin((time) * timeFactor + (vPosition.x + vPosition.y + vPosition.z) * posFactor) + 1.0) / 2.0, exponent);
	vPosition = vPosition + vNormal * ripple;

	gl_Position = projection * view * vec4(vPosition, 1.0);
}
