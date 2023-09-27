#version 460 core

in vec4 vPosition;
in vec3 vNormal;
in vec3 vColor;
in vec2 vTexcoord;

out vec4 fColor;

uniform float time;
uniform vec2 resolution;

void main() {
	vec2 uv = gl_FragCoord.xy/resolution.yx;
	fColor = vec4(abs(sin(uv.x*3 + time*3)), abs(cos(uv.x*3 + time*1))*abs(cos(uv.y*3 + time*-1)), abs(sin(uv.y*3 + time*2)), 1.0);
}
