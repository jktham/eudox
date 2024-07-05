#version 460 core

in vec2 aPosition;
in vec2 aTexcoord;

out vec2 vPosition;
out vec2 vTexcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;
uniform vec2 resolution;
uniform vec3 color;

void main() {
    vPosition = aPosition;
    vTexcoord = aTexcoord;
    gl_Position = vec4(aPosition, 0.0, 1.0);
}
