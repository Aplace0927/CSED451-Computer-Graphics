#version 330 core

in vec3 outVec3FragPos;
in vec3 outVec3Normal;
in vec2 outVec2TexCoord;
in vec4 outGouraudColor;
in mat3 outTBN;

out vec4 FragColor;

// --- Uniforms ---
uniform sampler2D samp2DTexture; // Diffuse Map
uniform sampler2D normalMap;     // Normal Map
uniform float uFloatUseTexture;
uniform float uFloatUseNormalMap;
uniform vec3 uColor;             // Object Color
uniform vec3 uVec3ViewPos;       // Camera Position
uniform int uIntShadingMode;     // 0: Gouraud, 1: Phong, 2: Phong+Normal

// --- Lights ---
struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirectionalLight dirLight;

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define SHININESS 32.0
#define DISTANCE_FACTOR 64.0
#define TEXTURE_SCALE 500.0
#define NR_POINT_LIGHTS 16

uniform PointLight pointLights[NR_POINT_LIGHTS];

// --- Function Prototypes ---
vec3 CalcGouraudDirLight(DirectionalLight dirLight, vec3 normal, vec3 viewDir, vec3 color);
vec3 CalcGouraudPointLight(PointLight pointLight, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 color);
vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir, vec3 color);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 color);

void main() {
    // 0. Base Color
    vec4 texColor = texture(samp2DTexture, outVec2TexCoord);
    vec3 objectColor = mix(uColor, texColor.rgb, uFloatUseTexture);
    vec3 norm = normalize(outVec3Normal);

    vec3 viewDir = normalize(uVec3ViewPos - outVec3FragPos);
    vec3 result = vec3(0.0, 0.0, 0.0);

    // 1. Gouraud Shading (supports directional + point lights)
    if (uIntShadingMode == 0) {
        result = CalcGouraudDirLight(dirLight, norm, viewDir, objectColor);
        for (int i = 0; i < NR_POINT_LIGHTS; i++) {
            result += CalcGouraudPointLight(pointLights[i], norm, outVec3FragPos, viewDir, objectColor);
        }

        FragColor = vec4(result * objectColor, 1.0);
        return;
    }

    // 2. Normal Vector
    if (uIntShadingMode == 2) {
        vec3 normalFromMap = texture(normalMap, outVec2TexCoord * TEXTURE_SCALE).rgb;
        normalFromMap = normalize(normalFromMap * 2.0 - 1.0);
        norm = normalize(outTBN * normalFromMap);
    }

    // 3. Directional Light
    result += CalcDirLight(dirLight, norm, viewDir, objectColor);
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, outVec3FragPos, viewDir, objectColor);

    FragColor = vec4(result, 1.0);
}

vec3 CalcGouraudDirLight(DirectionalLight dirLight, vec3 normal, vec3 viewDir, vec3 color) {
    // Directional light contribution
    vec3 lightDir = normalize(-dirLight.direction);
    
    vec3 ambient = dirLight.ambient;

    float diffIntensity = max(dot(normal, lightDir), 0.0);
    vec3 diffused = dirLight.diffuse * diffIntensity;

    vec3 reflDir = reflect(-lightDir, normal);

    float specIntensity = pow(max(dot(viewDir, reflDir), 0.0), SHININESS);
    vec3 specular = dirLight.specular * specIntensity;

    return (ambient + diffused + specular);
}

vec3 CalcGouraudPointLight(PointLight pointLight, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 color) {
    // Point light contribution
    vec3 lightDir = normalize(pointLight.position - fragPos);
    
    vec3 ambient = pointLight.ambient;

    float diffIntensity = max(dot(normal, lightDir), 0.0);
    vec3 diffused = pointLight.diffuse * diffIntensity;

    vec3 reflDir = reflect(-lightDir, normal);

    float specIntensity = pow(max(dot(viewDir, reflDir), 0.0), SHININESS);
    vec3 specular = pointLight.specular * specIntensity;

    // Attenuation
    float distance    = length(pointLight.position - fragPos) / DISTANCE_FACTOR;
    
    // Safety Fix
    float attenuationDenominator = pointLight.constant + pointLight.linear * distance + 
                                   pointLight.quadratic * (distance * distance);
                                   
    float attenuation = 0.0;
    if (attenuationDenominator > 0.0001) {
        attenuation = 1.0 / attenuationDenominator;
    }

    return (ambient + diffused + specular) * attenuation;
}

// Directional Light
vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir, vec3 color) {
    vec3 lightDir = normalize(-light.direction);
    
    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    
    // Specular (Phong)
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), SHININESS); // Shininess = 32
    
    vec3 ambient  = light.ambient  * color;
    vec3 diffuse  = light.diffuse  * diff * color;
    vec3 specular = light.specular * spec * vec3(1.0);
    
    return (ambient + diffuse + specular);
}

// Point Light
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 color) {
    vec3 lightDir = normalize(light.position - fragPos);
    
    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    
    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), SHININESS); // Shininess = 32
    
    // Attenuation
    float distance    = length(light.position - fragPos) / DISTANCE_FACTOR;
    
    // Safety Fix
    float attenuationDenominator = light.constant + light.linear * distance + 
                                   light.quadratic * (distance * distance);
                                   
    float attenuation = 0.0;
    if (attenuationDenominator > 0.0001) {
        attenuation = 1.0 / attenuationDenominator;
    }

    vec3 ambient  = light.ambient  * color;
    vec3 diffuse  = light.diffuse  * diff * color;
    vec3 specular = light.specular * spec * vec3(1.0);
    
    return (ambient + diffuse + specular) * attenuation;
}