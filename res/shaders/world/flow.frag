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

layout (binding = 0) uniform sampler2D baseTexture;
layout (binding = 1) uniform sampler2D flowTexture;

uniform float flowSpeed = 0.01;

void main() {
    vec4 flow = (texture(flowTexture, vTexcoord) - 1.0 / 510.0) * 2.0 - 1.0;
    vec2 uv = vTexcoord + vec2(flow.r, flow.g) * flowSpeed * time;
	uv = fract(uv - 0.0001) + 0.0001;

	if (texture(baseTexture, uv).a < 0.5) discard;
	fColor = vec4(vColor, 1.0) * texture(baseTexture, uv);
	fDepth = vec3(gl_FragCoord.z / gl_FragCoord.w);
	fPosition = vPosition;
	fNormal = normalize(vNormal);
	fMask = mask;
}
