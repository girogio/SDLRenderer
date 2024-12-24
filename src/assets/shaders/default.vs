#version 410 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 avecNormal;
layout(location = 2) in vec2 aTexCoord;

struct Camera {
    vec3 position;
    mat4 view;
    mat4 projection;
};

uniform mat4 model;

uniform Camera camera;

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_normal1;
    sampler2D texture_specular1;
};

uniform Material material;
uniform mat3 normalMatrix;

out vec3 fragPos;
out vec2 texCoord;
out vec3 normal;

out Camera cameraStruct;

vec3 transformNormal(vec3 normalvec) {
    return (mat3(transpose(inverse(model))) * normalvec);
}

void main() {
    texCoord = aTexCoord;
    fragPos = vec3(model * vec4(aPos, 1.0));
    cameraStruct = camera;
    normal = normalMatrix * avecNormal;
    gl_Position = camera.projection * camera.view * model * vec4(aPos, 1.0);
}
