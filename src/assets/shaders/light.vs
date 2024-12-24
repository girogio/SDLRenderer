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

out vec3 fragPos;
out vec2 texCoord;
out vec3 normal;

out Camera cameraStruct;

void main() {
    gl_Position = camera.projection * camera.view * model * vec4(aPos, 1.0);
}
