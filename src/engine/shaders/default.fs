#version 330 core

in vec2 texCoord;

#define MAX_DIFFUSE_TEXTURES 16
#define MAX_SPECULAR_TEXTURES 16

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

uniform sampler2D diffuse_textures[MAX_DIFFUSE_TEXTURES];
uniform sampler2D specular_textures[MAX_SPECULAR_TEXTURES];

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 0.5, 0.2, 1.0);

    vec4 diffuseColor = vec4(material.diffuse, 1.0);
    vec4 specularColor = vec4(material.specular, 1.0);

    // for(int i = 0; i < MAX_DIFFUSE_TEXTURES; i++) {
    //     if(diffuse_textures[i] != 0) {
    //         diffuseColor *= texture(diffuse_textures[i], texCoord);
    //     }
    // }

    FragColor = diffuseColor + specularColor;

}
