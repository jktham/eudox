#version 460 core

in vec3 vPosition;
in vec3 vNormal;
in vec3 vColor;
in vec2 vTexcoord;

layout (location = 0) out vec4 fColor;
layout (location = 1) out vec3 fPosition;
layout (location = 2) out vec3 fNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;
uniform vec2 resolution;
uniform vec3 color;
uniform vec3 viewPos;
uniform mat4 uiProjection;
uniform float u[32]; // ambient, diffuse, specular, shininess, lightPos.xyz

layout (binding = 0) uniform sampler2D texture0;
layout (binding = 1) uniform sampler2D texture1;

void main() {
	vec3 norm = normalize(vNormal);
	vec3 lightPos = vec3(u[4], u[5], u[6]);
    vec3 lightDir = normalize(lightPos - vPosition);
    vec3 viewDir = normalize(viewPos - vPosition);
    vec3 reflectDir = reflect(-lightDir, norm);

    float ambient = u[0];
    float diffuse = u[1] * max(dot(norm, lightDir), 0.0);
    float specular = u[2] * pow(max(dot(viewDir, reflectDir), 0.0), u[3]);

    vec3 result = vColor * (ambient + diffuse + specular);

	fColor = vec4(result, 1.0) * texture(texture0, vTexcoord.st);
	fPosition = vPosition;
	fNormal = normalize(vNormal);
}
