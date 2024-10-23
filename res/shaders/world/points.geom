#version 460 core

layout (triangles) in;
layout (points, max_vertices = 3) out;

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
uniform mat4 inverseView;
uniform float fov;
uniform uvec3 mask;

uniform float pointSize = 1.0;

void point(int i) {
	vPosition = vs_out[i].vPosition;
	vNormal = vs_out[i].vNormal;
	vColor = vs_out[i].vColor;
	vTexcoord = vs_out[i].vTexcoord;
	gl_Position = projection * view * vec4(vPosition, 1.0);
    EmitVertex();

	EndPrimitive();
}

void main() {
	gl_PointSize = pointSize;

	point(0);
	point(1);
	point(2);
}
