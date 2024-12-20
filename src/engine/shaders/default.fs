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

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 0.5, 0.2, 1.0);

}
