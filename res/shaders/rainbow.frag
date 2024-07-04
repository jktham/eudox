#version 460 core

in vec3 vPosition;
in vec3 vNormal;
in vec3 vColor;
in vec2 vTexcoord;

out vec4 fColor;

uniform float time;
uniform vec2 resolution;
uniform float u[32];

void main() {
	vec2 uv = gl_FragCoord.xy/resolution.yx;
	float t = time * u[0];
	fColor = vec4(abs(sin(uv.x*3 + t*3)), abs(cos(uv.x*3 + t*1))*abs(cos(uv.y*3 + t*-1)), abs(sin(uv.y*3 + t*2)), 1.0);
}
