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

uniform float noiseScale = 4.0;

float random(vec2 st) {
	return fract(sin(dot(st.xy, vec2(12.9898,78.233))) * 43758.5453123);
}

void main() {
	vec4 screen = projection * view * vec4(vPosition, 1.0);
	vec2 uv = (screen.xy / screen.w + vec2(1.0)) / 2.0;
	vec2 xy = floor(uv * resolution / noiseScale) / resolution;
	vec3 col = vec3(random(xy * 1.0 + time), random(xy * 2.0 + time), random(xy * 3.0 + time));

	fColor = vec4(col * vColor, 1.0);
	fDepth = vec3(gl_FragCoord.z / gl_FragCoord.w);
	fPosition = vPosition;
	fNormal = normalize(vNormal);
	fMask = mask;
}
