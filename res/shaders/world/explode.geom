#version 460 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

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
uniform vec3 light;
uniform vec3 viewPos;
uniform mat4 uiProjection;
uniform float u[32];

void main() {
	vPosition = vs_out[0].vPosition + vs_out[0].vNormal * 0.5 * sin(time);
	vNormal = vs_out[0].vNormal;
	vColor = vs_out[0].vColor;
	vTexcoord = vs_out[0].vTexcoord;
	gl_Position = projection * view * vec4(vPosition, 1.0);
    EmitVertex();

	vPosition = vs_out[1].vPosition + vs_out[1].vNormal * 0.5 * sin(time);
	vNormal = vs_out[1].vNormal;
	vColor = vs_out[1].vColor;
	vTexcoord = vs_out[1].vTexcoord;
	gl_Position = projection * view * vec4(vPosition, 1.0);
    EmitVertex();

	vPosition = vs_out[2].vPosition + vs_out[2].vNormal * 0.5 * sin(time);
	vNormal = vs_out[2].vNormal;
	vColor = vs_out[2].vColor;
	vTexcoord = vs_out[2].vTexcoord;
	gl_Position = projection * view * vec4(vPosition, 1.0);
    EmitVertex();

    EndPrimitive();
}
