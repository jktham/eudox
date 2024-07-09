#version 460 core

in vec3 vPosition;
in vec3 vNormal;
in vec3 vColor;
in vec2 vTexcoord;

layout (location = 0) out vec4 fColor;
layout (location = 1) out vec3 fDepth;
layout (location = 2) out vec3 fPosition;
layout (location = 3) out vec3 fNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;
uniform vec2 resolution;
uniform vec3 color;
uniform vec3 viewPos;
uniform mat4 uiProjection;
uniform float u[32];

layout (binding = 0) uniform sampler2D texture0;
layout (binding = 1) uniform sampler2D texture1;

float random(vec2 st) {
	return fract(sin(dot(st.xy, vec2(12.9898,78.233))) * 43758.5453123);
}

void main() {
	vec4 screen = projection * view * vec4(vPosition, 1.0);
	vec2 uv = (screen.xy / screen.w + vec2(1.0)) / 2.0;
	float scale = 4.0;
	vec2 xy = floor(uv * resolution / scale) / resolution;
	vec3 col = vec3(random(xy * 1.0 + time), random(xy * 2.0 + time), random(xy * 3.0 + time));

	fColor = vec4(col * vColor, 1.0);
	fDepth = vec3(gl_FragCoord.z / gl_FragCoord.w);
	fPosition = vPosition;
	fNormal = normalize(vNormal);
}
