#version 460 core

in vec2 aPosition;
in vec2 aTexcoord;

out vec4 vPosition;
out vec2 vTexcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;
uniform vec2 resolution;
uniform vec3 color;

void main() {
    vPosition = vec4(aPosition.x, aPosition.y, 0.0, 1.0);
    vTexcoord = aTexcoord;
    gl_Position = vPosition;
}
