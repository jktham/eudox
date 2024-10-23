#version 460 core

in vec3 vPosition;
in vec3 vNormal;
in vec3 vColor;
in vec2 vTexcoord;

layout (location = 0) out vec4 fColor;
layout (location = 1) out vec3 fDepth;
layout (location = 2) out vec3 fPosition;
layout (location = 3) out vec3 fNormal;
layout (location = 4) out uvec3 fMask;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;
uniform vec2 resolution;
uniform vec3 viewPos;
uniform mat4 uiProjection;
uniform float u[32];
uniform mat4 inverseView;
uniform float fov;
uniform uvec3 mask;

layout (binding = 0) uniform sampler2D texture0;
layout (binding = 1) uniform sampler2D texture1;

uniform vec3 light = vec3(0.0, 0.0, 0.0);
uniform float ambientStrength = 0.1;
uniform float diffuseStrength = 0.6;
uniform float specularStrength = 0.3;
uniform float specularExponent = 32.0;

void main() {
	vec3 norm = normalize(vNormal);
	vec3 lightPos = light;
    vec3 lightDir = normalize(lightPos - vPosition);
    vec3 viewDir = normalize(viewPos - vPosition);
    vec3 reflectDir = reflect(-lightDir, norm);

    float ambient = ambientStrength;
    float diffuse = diffuseStrength * max(dot(norm, lightDir), 0.0);
    float specular = specularStrength * pow(max(dot(viewDir, reflectDir), 0.0), specularExponent);

    vec3 result = vColor * (ambient + diffuse + specular);

    fColor = vec4(result, 1.0);
	fDepth = vec3(gl_FragCoord.z / gl_FragCoord.w);
	fPosition = vPosition;
	fNormal = normalize(vNormal);
	fMask = mask;
}
