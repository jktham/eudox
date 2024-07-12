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
uniform vec3 color;
uniform vec3 viewPos;
uniform mat4 uiProjection;
uniform float u[32];

void line(int i) {
	vPosition = vs_out[i].vPosition;
	vNormal = vs_out[i].vNormal;
	vColor = abs(vs_out[i].vNormal);
	vTexcoord = vs_out[i].vTexcoord;
	gl_Position = projection * view * vec4(vPosition, 1.0);
    EmitVertex();

	vPosition = vs_out[i].vPosition + vs_out[i].vNormal * 0.2;
	vNormal = vs_out[i].vNormal;
	vColor = abs(vs_out[i].vNormal);
	vTexcoord = vs_out[i].vTexcoord;
	gl_Position = projection * view * vec4(vPosition, 1.0);
    EmitVertex();

	EndPrimitive();
}

void main() {
	line(0);
	line(1);
	line(2);
}
