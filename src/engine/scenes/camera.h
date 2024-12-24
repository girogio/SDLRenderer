#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../shader.h"

#ifndef CAMERAMOVEMENT
#define CAMERAMOVEMENT
enum CameraMovement
{
    NONE,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
};
#endif

class Camera
{

public:
    glm::mat4 projectionMat;
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    std::string cameraUniformName = "camera.";

    bool invertPitch = true;

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    Camera(glm::mat4 projectionMat, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = -90.0f,
           float pitch = 0.0f,
           float zoom = 90.0f)
        : front(glm::vec3(0.0f, 0.0f, -1.0f)),
          movementSpeed(2.5f),
          mouseSensitivity(0.1f),
          zoom(90.0f)
    {
        this->projectionMat = projectionMat;
        this->position = position;
        this->worldUp = up;
        this->yaw = yaw;
        this->pitch = pitch;
        this->zoom = zoom;
        updateCameraVectors();
    }

    Camera(const Camera &camera)
    {
        this->projectionMat = camera.projectionMat;
        this->position = camera.position;
        this->front = camera.front;
        this->up = camera.up;
        this->right = camera.right;
        this->worldUp = camera.worldUp;
        this->yaw = camera.yaw;
        this->pitch = camera.pitch;
        this->movementSpeed = camera.movementSpeed;
        this->mouseSensitivity = camera.mouseSensitivity;
        this->zoom = camera.zoom;
    }

    void turnTowards(glm::vec3 target)
    {
        glm::vec3 direction = glm::normalize(target - position);
        pitch = glm::degrees(asin(direction.y));
        yaw = glm::degrees(atan2(direction.z, direction.x));
        updateCameraVectors();
    }

    glm::mat4 getViewMatrix() const
    {
        return glm::lookAt(position, position + front, up);
    }

    glm::mat4 getProjectionMatrix() const
    {
        return projectionMat;
    }

    void processKeyboard(CameraMovement direction, float deltaTime)
    {
        float velocity = movementSpeed * deltaTime;

        if (direction == FORWARD)
            position += glm::vec3(front.x, 0.0f, front.z) * velocity;
        if (direction == BACKWARD)
            position -= glm::vec3(front.x, 0.0f, front.z) * velocity;
        if (direction == LEFT)
            position -= glm::vec3(right.x, 0.0f, right.z) * velocity;
        if (direction == RIGHT)
            position += glm::vec3(right.x, 0.0f, right.z) * velocity;
    }

    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
    {
        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        yaw += xoffset;
        pitch += invertPitch ? -yoffset : yoffset;

        if (constrainPitch)
        {
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
        }

        updateCameraVectors();
    }

    void processMouseScroll(float yoffset)
    {
        if (zoom >= 1.0f && zoom <= 90.0f)
            zoom -= yoffset;
        if (zoom <= 1.0f)
            zoom = 1.0f;
        if (zoom >= 90.0f)
            zoom = 90.0f;
    }

    void bind(Shader &shader)
    {
        shader.setVec3(cameraUniformName + "position", position);
        shader.setMat4(cameraUniformName + "view", getViewMatrix());
        shader.setMat4(cameraUniformName + "projection", getProjectionMatrix());
    }

    std::string generateShaderStruct() const
    {
        return "struct Camera {\n"
               "    mat4 view;\n"
               "    vec3 position;\n"
               "    mat4 projection;\n"
               "};\n"
               "uniform Camera camera;\n";
    }

private:
    void updateCameraVectors()
    {
        glm::vec3 newFront;
        newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        newFront.y = sin(glm::radians(pitch));
        newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(newFront);

        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }
};
