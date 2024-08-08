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
uniform vec3 viewPos;
uniform mat4 uiProjection;
uniform float u[32];

layout (binding = 0) uniform sampler2D texture0;
layout (binding = 1) uniform sampler2D texture1;

void main() {
	// vec2 uv = gl_FragCoord.xy / resolution;
	vec3 ray = vPosition - viewPos;
	float r = length(ray);
	float phi = sign(ray.z) * acos(ray.x / sqrt(ray.x*ray.x + ray.z*ray.z));
	float theta = acos(ray.y / r);
	vec2 uv = vec2((phi / 3.1415 + 1.0) / 2.0, 1.0 - theta / 3.1415);

	fColor = vec4(vColor, 1.0) * texture(texture0, uv);
	fDepth = vec3(gl_FragCoord.z / gl_FragCoord.w);
	fPosition = vPosition;
	fNormal = normalize(vNormal);
}
