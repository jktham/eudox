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
uniform mat4 inverseView;
uniform float fov;

layout (binding = 0) uniform sampler2D texture0;
layout (binding = 1) uniform sampler2D texture1;

uniform vec3 light = vec3(0.0, 0.0, 0.0);
uniform vec4 spherePos = vec4(0.0, 0.0, 0.0, 1.0);
uniform vec3 sphereCol = vec3(1.0, 1.0, 1.0);
uniform vec3 sphereBgCol = vec3(0.0, 0.0, 0.0);
uniform int sphereNoBg = 0;

struct Ray {
	vec3 origin;
	vec3 direction;
};

float far = 10000.0;
float near = 0.001;
const float PI = 3.1415926;
const int MAX_OBJECTS = 60;

float intersectSphere(Ray ray, vec4 position) {
	float a = dot(ray.direction, ray.direction);
	vec3 offset = ray.origin - position.xyz;
	float b = 2.0 * dot(ray.direction, offset);
	float c = dot(offset, offset) - (position.w*position.w);
	if (b*b - 4.0*a*c < 0.0) {
		return -1.0;
	}
	return (-b - sqrt((b*b) - 4.0*a*c))/(2.0*a);
}

void main() {
	vec2 uv = gl_FragCoord.xy / resolution - vec2(0.5);
	uv.y *= resolution.y/resolution.x;
	uv *= 2.26; // magic idk

	vec3 cameraPos = vec3(inverseView * vec4(0.0, 0.0, 0.0, 1.0));
	vec3 cameraDir = vec3(inverseView * vec4(0.0, 0.0, -1.0, 0.0));
	vec3 rayOffset = vec3(inverseView * vec4(uv.x, uv.y, 0.0, 0.0));

	vec3 rayDir = normalize(cameraDir + rayOffset * fov / 180.0 * PI);
	Ray r = Ray(cameraPos, rayDir);
	vec4 s = spherePos;

	vec4 color = vec4(sphereBgCol, 1.0);
	float t = intersectSphere(r, s);
	if (t > near && t < far) {
		color = vec4(sphereCol, 1.0);
	} else if (sphereNoBg == 1) {
		discard;
	}

	fColor = color;
	fDepth = rayDir * t;
	fPosition = cameraPos + rayDir * t;
	fNormal = normalize(-rayDir);
}

