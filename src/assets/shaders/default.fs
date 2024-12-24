#version 410 core

#define gamma 2.2

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
    sampler2D texture_normal1;
    sampler2D texture_specular1;
};

in vec2 texCoord;
in vec3 fragPos;
in vec3 normal;
in Camera cameraStruct;

uniform Light light;
uniform Material material;

out vec4 FragColor;

const bool blinn = true;

void main() {
    vec3 diffuseColor = texture(material.texture_diffuse1, texCoord).rgb;
    vec3 specularColor = texture(material.texture_specular1, texCoord).rgb;

    // Ambient lighting
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    // Specular lighting
    vec3 viewDir = normalize(cameraStruct.position - fragPos);
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

    vec3 ambient = light.ambientCol * diffuseColor;
    vec3 diffuse = light.diffuseCol * diff * diffuseColor;
    vec3 specular = light.specularCol * spec * specularStrength * specularColor;

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.const_lin_quad.x + light.const_lin_quad.y * distance + light.const_lin_quad.z * distance * distance);

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 color = ambient + diffuse + specular;

    FragColor = vec4(pow(color, vec3(gamma)), 1.0);
}
