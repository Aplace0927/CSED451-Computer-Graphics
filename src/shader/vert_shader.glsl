#version 330 core

layout (location = 0) in vec3 inVec3Position;
layout (location = 1) in vec3 inVec3Normal;
layout (location = 2) in vec2 inVec2TexCoord;
layout (location = 3) in vec3 inVec3Tangent;

uniform mat4 uMat4View;
uniform mat4 uMat4Projection;
uniform mat4 uMat4Model;

uniform int uIntShadingMode;

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirectionalLight dirLight;
uniform vec3 uVec3ViewPos;
uniform vec3 uColor;

out vec3 outVec3FragPos;
out vec3 outVec3Normal;
out vec2 outVec2TexCoord;
out vec4 outGouraudColor;
out mat3 outTBN;

void main() {
    vec4 worldPos = uMat4Model * vec4(inVec3Position, 1.0);
    outVec3FragPos = worldPos.xyz;
    outVec2TexCoord = inVec2TexCoord;
    
    // Normal Matrix Calculate
    mat3 normalMatrix = transpose(inverse(mat3(uMat4Model)));
    outVec3Normal = normalize(normalMatrix * inVec3Normal);

    // TBN Matrix Calculate
    vec3 T = normalize(normalMatrix * inVec3Tangent);
    vec3 N = normalize(normalMatrix * inVec3Normal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    outTBN = mat3(T, B, N);

    gl_Position = uMat4Projection * uMat4View * worldPos;

    // --- Gouraud Shading Calculation ---
    if (uIntShadingMode == 0) {
        vec3 ambient = dirLight.ambient;

        // Diffuse
        vec3 norm = normalize(outVec3Normal);
        vec3 lightDir = normalize(-dirLight.direction);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = dirLight.diffuse * diff;

        // Specular
        vec3 viewDir = normalize(uVec3ViewPos - outVec3FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
        vec3 specular = dirLight.specular * spec;

        outGouraudColor = vec4(ambient + diffuse + specular, 1.0);
    } else {
        outGouraudColor = vec4(0.0);
    }
}