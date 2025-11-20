#version 330 core

layout (location = 0) in vec3 inVec3Position;
layout (location = 1) in vec3 inVec3Normal;

uniform mat4 uMat4Projection;
uniform mat4 uMat4Model;

out vec3 outVec3WorldPosition;

void main() {
    vec4 worldPosition = uMat4Projection * uMat4Model * vec4(inVec3Position, 1.0);
    gl_Position = worldPosition;
    outVec3WorldPosition = worldPosition.xyz;
}