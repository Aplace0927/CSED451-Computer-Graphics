#version 330 core

in vec3 inFragVec3Position;
in vec3 inFragVec3Normal;
in vec2 outVec2TexCoord;

uniform sampler2D samp2DTexture;

uniform vec3 uColor;
uniform float uFloatUseTexture;
out vec4 FragColor;

void main() {
    FragColor = mix(texture(samp2DTexture, outVec2TexCoord), vec4(uColor, 1.0), 1.0 - uFloatUseTexture);
}