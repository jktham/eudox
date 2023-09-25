#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec3 vColor;
layout (location = 3) in vec2 vTexcoord;

layout (location = 0) out vec4 fColor;

void main() {
    float ambient = 0.2;
	vec3 lightDir = normalize(vec3(1.0, 10.0, 5.0));
	float diffuse = max(dot(normalize(vNormal), lightDir), 0.0);
	vec3 result = (ambient + diffuse) * vColor;
	fColor = vec4(result, 1.0);
}
