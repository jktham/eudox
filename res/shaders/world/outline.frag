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

uniform float outlineWidth = 0.01;

void main() {
	fColor = vec4(vColor, 1.0);
	float scale = sqrt(model[0][0] * model[0][0] + model[0][1] * model[0][1] + model[0][2] * model[0][2]);
	// float angle = abs(dot(normalize(viewPos - vPosition), vNormal));
	
	float stroke = outlineWidth / gl_FragCoord.w / scale;
	if (vTexcoord.x < stroke || vTexcoord.x > 1.0 - stroke || vTexcoord.y < stroke || vTexcoord.y > 1.0 - stroke) {
		fColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
	fDepth = vec3(gl_FragCoord.z / gl_FragCoord.w);
	fPosition = vPosition;
	fNormal = normalize(vNormal);
	fMask = mask;
}
