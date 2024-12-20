#version 330 core

in vec2 texCoord;

#define MAX_DIFFUSE_TEXTURES 16
#define MAX_SPECULAR_TEXTURES 16

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

out vec4 FragColor;

void main() {
    vec4 diffuseColor = texture(texture_diffuse1, texCoord);
    // vec4 specularColor = texture(texture_specular1, texCoord);
    // vec4 normalColor = texture(texture_normal1, texCoord);

    FragColor = vec4(diffuseColor.rgb, 1.0);
}
