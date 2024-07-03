#version 460 core

in vec4 vPosition;
in vec2 vTexcoord;

out vec4 fColor;

uniform float time;
uniform float u[32];

layout (binding = 0) uniform sampler2D colorTexture;
layout (binding = 1) uniform sampler2D depthTexture;

void main() {
	vec4 t0 = vec4(vec3(1 - pow(texture(depthTexture, vTexcoord).r, 100)), 1.0);
    vec4 t1 = vec4(vec3(1.0 - texture(colorTexture, vTexcoord)), 1.0);
    fColor = mix(t0, t1, clamp((cos(time*u[0])*4+1)/2, 0, 1));
}
