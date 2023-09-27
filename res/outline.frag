#version 460 core

in vec4 vPosition;
in vec3 vNormal;
in vec3 vColor;
in vec2 vTexcoord;

out vec4 fColor;

void main() {
	fColor = vec4(vColor, 1.0);
	float stroke = 0.001 * gl_FragCoord.z / gl_FragCoord.w;
	if (vTexcoord.x < stroke || vTexcoord.x > 1.0 - stroke || vTexcoord.y < stroke || vTexcoord.y > 1.0 - stroke) {
		fColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
}
