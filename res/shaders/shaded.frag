#version 460 core

in vec3 vPosition;
in vec3 vNormal;
in vec3 vColor;
in vec2 vTexcoord;

out vec4 fColor;

uniform float u[32]; // ambient, diffuse, specular, shininess, lightPos.xyz
uniform vec3 viewPos;

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

    fColor = vec4(result, 1.0);
}
