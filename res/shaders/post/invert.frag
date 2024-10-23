#version 460 core

in vec3 vPosition;
in vec3 vNormal;
in vec3 vColor;
in vec2 vTexcoord;

out vec4 fColor;

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

uniform float invertSpeed = 1.0;

void main() {
	vec4 t0 = vec4(vec3(texture(texture0, vTexcoord)), 1.0);
    vec4 t1 = vec4(vec3(1.0 - texture(texture0, vTexcoord)), 1.0);
    fColor = mix(t0, t1, clamp((cos(time * invertSpeed)*4+1)/2, 0, 1));
}
