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
uniform vec3 color;
uniform vec3 viewPos;
uniform mat4 uiProjection;
uniform float u[32];

layout (binding = 0) uniform sampler2D texture0;
layout (binding = 1) uniform sampler2D texture1;

void main() {
    // vec2 xy_small = floor(mod(floor(vTexcoord * resolution), 256 * 1) / 1);
    // vec2 xy_large = floor(mod(floor(vTexcoord * resolution), 256 * 256) / 256);
    // if (mod(xy_large.x, 2) == 1) {
    //     xy_small.x = 255 - xy_small.x;
    // }
    // if (mod(xy_large.y, 2) == 1) {
    //     xy_small.y = 255 - xy_small.y;
    // }
    // vec2 rg = xy_small / 255;
    // vec2 ba = xy_large / 255;
    // fColor = vec4(rg.x, rg.y, ba.x, 1.0 - ba.y);

    vec4 distort = texture(texture1, vTexcoord);
    if (mod(floor(distort.b * 256), 2) == 1) {
        distort.r = 1.0 - distort.r;
    }
    if (mod(floor((1.0 - distort.a) * 256), 2) == 1) {
        distort.g = 1.0 - distort.g;
    }
    vec2 uv = (vec2(distort.r * 256, distort.g * 256) + vec2(distort.b * 256 * 256, (1.0 - distort.a) * 256 * 256)) / resolution * 0.9964;
    fColor = texture(texture0, uv);
}
