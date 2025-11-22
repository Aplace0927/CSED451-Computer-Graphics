#version 330 core

layout (location = 0) in vec3 inVec3Position;
layout (location = 1) in vec3 inVec3Normal;
layout (location = 2) in vec2 inVec2TexCoord;

uniform mat4 uMat4CameraShake;
uniform mat4 uMat4Projection;
uniform mat4 uMat4Model;

out vec3 outVec3WorldPosition;

void main() {
    vec4 worldPosition = uMat4Projection * uMat4Model * vec4(inVec3Position, 1.0);
    gl_Position = uMat4CameraShake * worldPosition;
    outVec3WorldPosition = worldPosition.xyz;
}