#version 330 core
out vec4 FragColor;

in vec3 texCoords;

uniform samplerCube sampCubeSkyBox;

void main()
{    
    FragColor = texture(sampCubeSkyBox, texCoords);
}
