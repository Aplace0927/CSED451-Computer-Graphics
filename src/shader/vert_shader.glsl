#version 330 core

layout (location = 0) in vec3 inVec3Position;
layout (location = 1) in vec3 inVec3Normal;
layout (location = 2) in vec2 inVec2TexCoord;

uniform mat4 uMat4View;
uniform mat4 uMat4Projection;
uniform mat4 uMat4Model;
uniform mat4 uMat4CameraShake;

out vec3 outVec3WorldPosition;
out vec2 outVec2TexCoord;

void main() {
    vec4 worldPos = uMat4Model * vec4(inVec3Position, 1.0);
    outVec3WorldPosition = worldPos.xyz;
    outVec2TexCoord = inVec2TexCoord;
    
    gl_Position = uMat4Projection * uMat4CameraShake * uMat4View * worldPos;
}