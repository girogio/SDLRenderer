#version 410 core

out vec4 FragColor;

struct Camera {
    vec3 position;
    mat4 view;
    mat4 projection;
};

uniform Camera camera;

uniform mat4 model;

void main() {
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
