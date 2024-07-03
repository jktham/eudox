#version 460 core

in vec4 vPosition;
in vec3 vNormal;
in vec3 vColor;
in vec2 vTexcoord;

out vec4 fColor;

uniform float u[32]; // ambient, light.x, light.y, light.z

void main() {
    float ambient = u[0];
	vec3 lightDir = normalize(vec3(u[1], u[2], u[3]));
	float diffuse = max(dot(normalize(vNormal), lightDir), 0.0);
	vec3 result = (ambient + diffuse) * vColor;
	fColor = vec4(result, 1.0);
}
