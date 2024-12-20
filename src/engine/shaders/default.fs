#version 330 core

in vec2 texCoord;

#define MAX_DIFFUSE_TEXTURES 16
#define MAX_SPECULAR_TEXTURES 16

uniform sampler2D diffuse_textures0;
uniform sampler2D specular_texture0;

out vec4 FragColor;

void main() {
    vec4 diffuseColor = texture(diffuse_textures0, texCoord);
    // vec4 specularColor = texture(specular_texture0, texCoord);

    FragColor = diffuseColor ;
}
