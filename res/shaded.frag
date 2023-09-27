#version 460 core

in vec4 vPosition;
in vec3 vNormal;
in vec3 vColor;
in vec2 vTexcoord;

out vec4 fColor;

void main() {
    float ambient = 0.2;
	vec3 lightDir = normalize(vec3(1.0, 10.0, 5.0));
	float diffuse = max(dot(normalize(vNormal), lightDir), 0.0);
	vec3 result = (ambient + diffuse) * vColor;
	fColor = vec4(result, 1.0);
}
