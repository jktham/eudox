#version 460 core

in vec3 vPosition;
in vec3 vNormal;
in vec3 vColor;
in vec2 vTexcoord;

layout (location = 0) out vec4 fColor;
layout (location = 1) out vec3 fPosition;
layout (location = 2) out vec3 fNormal;

uniform mat4 model;
uniform vec3 viewPos;

void main() {
	fColor = vec4(vColor, 1.0);
	float scale = sqrt(model[0][0] * model[0][0] + model[0][1] * model[0][1] + model[0][2] * model[0][2]);
	// float angle = abs(dot(normalize(viewPos - vPosition), vNormal));
	float stroke = 0.01 / gl_FragCoord.w / scale;
	if (vTexcoord.x < stroke || vTexcoord.x > 1.0 - stroke || vTexcoord.y < stroke || vTexcoord.y > 1.0 - stroke) {
		fColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
	fPosition = vPosition;
	fNormal = normalize(vNormal);
}
