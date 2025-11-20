#version 330 core

layout (location = 0) in vec3 inVec3Position;
layout (location = 1) in vec3 inVec3Normal;

void main() {
    gl_Position = vec4(inVec3Position, 1.0);
}