#version 410 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 avecNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

struct Camera {
    vec3 position;
    mat4 view;
    mat4 projection;
};

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_normal1;
    sampler2D texture_specular1;
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

uniform mat4 model;
uniform Light light;
uniform Camera camera;

out vec3 fragPos;
out vec2 texCoord;
out vec3 normal;
out mat3 TBN;

out vec3 TangentLightPos;
out vec3 TangentViewPos;
out vec3 TangentFragPos;

void main() {
    texCoord = aTexCoord;
    fragPos = vec3(model * vec4(aPos, 1.0));

    vec3 T = normalize(vec3(model * vec4(aTangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(avecNormal, 0.0)));

    T = normalize(T - dot(T, N) * N);

    vec3 B = cross(N, T);

    TBN = transpose(mat3(T, B, N));

    TangentLightPos = TBN * light.position;
    TangentViewPos = TBN * camera.position;
    TangentFragPos = TBN * fragPos;

    gl_Position = camera.projection * camera.view * model * vec4(aPos, 1.0);
}
