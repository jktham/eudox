#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec3 vColor;
layout (location = 3) in vec2 vTexcoord;

layout (location = 0) out vec4 fColor;

layout (location = 3) uniform float time;
layout (location = 4) uniform vec2 resolution;

void main() {
	vec2 uv = gl_FragCoord.xy/resolution.yx;
	fColor = vec4(abs(sin(uv.x*3 + time*3)), abs(cos(uv.x*3 + time*1))*abs(cos(uv.y*3 + time*-1)), abs(sin(uv.y*3 + time*2)), 1.0);
}
