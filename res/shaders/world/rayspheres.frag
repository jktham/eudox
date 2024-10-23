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
uniform float ambientStrength = 0.1;
uniform float diffuseStrength = 0.6;
uniform float specularStrength = 0.3;
uniform float specularExponent = 32.0;
uniform vec4 spherePos[16];
uniform vec3 sphereCol[16];
uniform vec3 sphereBgCol = vec3(0.0, 0.0, 0.0);
uniform bool sphereNoBg = false;

struct Ray {
	vec3 origin;
	vec3 direction;
};

float far = 10000.0;
float near = 0.001;
const float PI = 3.1415926;

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
	Ray ray = Ray(cameraPos, rayDir);

	vec4 color = vec4(sphereBgCol, 1.0);
	vec3 normal = normalize(-rayDir);

	float t = far;
	int j = 0;
	for (int i = 0; i < 16; i++) {
		if (spherePos[i].w == 0.0) {
			continue;
		}
		float t2 = intersectSphere(ray, spherePos[i]);
		if (t2 > near && t2 < t || t < near) {
			t = t2;
			j = i;
		}
	}
	if (t > near && t < far) {
		normal = normalize(cameraPos + rayDir * t - spherePos[j].xyz);
		vec3 lightPos = light;
		vec3 lightDir = normalize(lightPos - (cameraPos + rayDir * t));
		vec3 viewDir = normalize(viewPos - (cameraPos + rayDir * t));
		vec3 reflectDir = reflect(-lightDir, normal);

		float ambient = ambientStrength;
		float diffuse = diffuseStrength * max(dot(normal, lightDir), 0.0);
		float specular = specularStrength * pow(max(dot(viewDir, reflectDir), 0.0), specularExponent);

		vec3 result = sphereCol[j] * (ambient + diffuse + specular);
		color = vec4(result, 1.0);
	} else if (sphereNoBg) {
		discard;
	}

	fColor = color;
	fDepth = rayDir * t;
	fPosition = cameraPos + rayDir * t;
	fNormal = normal;
}

