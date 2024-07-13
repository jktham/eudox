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

float random(vec2 st) {
	return fract(sin(dot(st.xy, vec2(12.9898,78.233))) * 43758.5453123);
}

void main() {
	float t = floor(time * 30);
	float d = 0.15;
	
	vec3 rnd = normalize(vec3(random(vs_out[0].vPosition.xy + vs_out[0].vNormal.xy + t + 0.00), random(vs_out[0].vPosition.xy + vs_out[0].vNormal.xy + t + 0.10), random(vs_out[0].vPosition.xy + vs_out[0].vNormal.xy + t + 0.20)));
	vPosition = vs_out[0].vPosition + rnd * d;
	vNormal = vs_out[0].vNormal;
	vColor = vs_out[0].vColor;
	vTexcoord = vs_out[0].vTexcoord;
	gl_Position = projection * view * vec4(vPosition, 1.0);
    EmitVertex();

	rnd = normalize(vec3(random(vs_out[1].vPosition.xy + vs_out[1].vNormal.xy + t + 0.01), random(vs_out[1].vPosition.xy + vs_out[1].vNormal.xy + t + 0.11), random(vs_out[1].vPosition.xy + vs_out[1].vNormal.xy + t + 0.21)));
	vPosition = vs_out[1].vPosition + rnd * d;
	vNormal = vs_out[1].vNormal;
	vColor = vs_out[1].vColor;
	vTexcoord = vs_out[1].vTexcoord;
	gl_Position = projection * view * vec4(vPosition, 1.0);
    EmitVertex();

	rnd = normalize(vec3(random(vs_out[2].vPosition.xy + vs_out[2].vNormal.xy + t + 0.02), random(vs_out[2].vPosition.xy + vs_out[2].vNormal.xy + t + 0.12), random(vs_out[2].vPosition.xy + vs_out[2].vNormal.xy + t + 0.22)));
	vPosition = vs_out[2].vPosition + rnd * d;
	vNormal = vs_out[2].vNormal;
	vColor = vs_out[2].vColor;
	vTexcoord = vs_out[2].vTexcoord;
	gl_Position = projection * view * vec4(vPosition, 1.0);
    EmitVertex();

    EndPrimitive();
}
