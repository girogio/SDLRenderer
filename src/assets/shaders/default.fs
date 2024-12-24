#version 410 core

struct Camera {
    vec3 position;
    mat4 view;
    mat4 projection;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 direction;
    vec3 specular;
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

    vec3 norm = normalize(normal);

    vec3 ambient = light.ambient * diffuseColor;
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    float specularStrength = 0.2;

    vec3 viewDir = normalize(cameraStruct.position - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = 0;

    if(blinn) {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(norm, halfwayDir), 0.0), 200);
    } else {
        spec = pow(max(dot(viewDir, reflectDir), 0.0), 800);
    }

    vec3 diffuse = light.diffuse * diff * diffuseColor;
    vec3 specular = light.specular * spec * specularStrength * specularColor;

    FragColor = vec4(ambient + diffuse + specular, 1.0);

    FragColor = pow(FragColor, vec4(2.2));
}
