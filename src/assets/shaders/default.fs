#version 410 core

const float gamma = 2.2;

struct Camera {
    vec3 position;
    mat4 view;
    mat4 projection;
};

struct Light {
    // Directionals
    vec3 position;
    vec3 ambient;

    // Colours
    mat3 colours;

    #define ambientCol colours[0]
    #define diffuseCol colours[1]
    #define specularCol colours[2]

    // Attenuation params
    vec3 const_lin_quad;
};

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    sampler2D texture_normal1;
};

in vec2 texCoord;
in vec3 fragPos;
in mat3 TBN;

in vec3 TangentLightPos;
in vec3 TangentViewPos;
in vec3 TangentFragPos;

uniform Material material;
uniform Light light;
uniform Camera camera;

out vec4 FragColor;

const bool blinn = false;

void main() {
    vec3 diffuseColor = texture(material.texture_diffuse1, texCoord).rgb;
    vec3 specularColor = texture(material.texture_specular1, texCoord).rgb;
    vec3 normalColor = texture(material.texture_normal1, texCoord).rgb;

    vec3 norm = normalize(normalColor * 2.0 - 1.0);

    // Ambient lighting
    vec3 lightDir = normalize(TangentLightPos - TangentFragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    // Specular lighting
    vec3 viewDir = normalize(TangentViewPos - TangentFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = 0;
    float specularStrength = 0.5;

    // Phong or Blinn-Phong?
    if(blinn) {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(norm, halfwayDir), 0.0), 200);
    } else {
        spec = pow(max(dot(viewDir, reflectDir), 0.0), 800);
    }

    // Combine results
    vec3 ambient = light.ambientCol * diffuseColor;
    vec3 diffuse = light.diffuseCol * diff * diffuseColor;
    vec3 specular = light.specularCol * spec * specularStrength * specularColor;

    // Attenuation
    float distance = length(TangentFragPos - TangentLightPos);
    float attenuation = 1.0 / (light.const_lin_quad.x + light.const_lin_quad.y * distance + light.const_lin_quad.z * distance * distance);

    // ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 color = ambient + diffuse + specular;

    FragColor = vec4(pow(color, vec3(gamma)), 1.0);
}
