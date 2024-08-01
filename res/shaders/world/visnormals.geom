#version 460 core

layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
	vec3 vPosition;
	vec3 vNormal;
	vec3 vColor;
	vec2 vTexcoord;
} vs_out[];

out vec3 vPosition;
out vec3 vNormal;
out vec3 vColor;
out vec2 vTexcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;
uniform vec2 resolution;
uniform vec3 viewPos;
uniform mat4 uiProjection;
uniform float u[32];

uniform float normalSize = 0.2;

void line(int i, float size) {
	vPosition = vs_out[i].vPosition;
	vNormal = vs_out[i].vNormal;
	vColor = vs_out[i].vColor;
	vTexcoord = vs_out[i].vTexcoord;
	gl_Position = projection * view * vec4(vPosition, 1.0);
    EmitVertex();

	vPosition = vs_out[i].vPosition + vs_out[i].vNormal * size;
	vNormal = vs_out[i].vNormal;
	vColor = vs_out[i].vColor;
	vTexcoord = vs_out[i].vTexcoord;
	gl_Position = projection * view * vec4(vPosition, 1.0);
    EmitVertex();

	EndPrimitive();
}

void main() {
	line(0, normalSize);
	line(1, normalSize);
	line(2, normalSize);
}
