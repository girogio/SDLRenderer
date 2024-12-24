#pragma once

#include <vector>
#include <string>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/io.hpp>

#include "camera.h"
#include "light.h"
#include "model.h"
#include "../managers/input.h"
#include "../shader.h"

class Scene
{
public:
    std::vector<Model> models;
    std::vector<Light> lights;
    std::vector<Camera> cameras;

    Node root;

    InputHandler inputHandler = InputHandler();

    unsigned int activeCamera = 0;

    Scene(const std::vector<Model> &models, const std::vector<Camera> &cameras, const std::vector<Light> &lights)
    {
        this->models = models;
        this->cameras = cameras;
        this->lights = lights;
    }

    // copy constructor
    Scene(const Scene &scene)
    {
        this->models = scene.models;
        this->cameras = scene.cameras;
        this->lights = scene.lights;
    }

    void processSDLEvents(SDL_Event event)

    {
        switch (event.type)
        {
        case SDL_MOUSEMOTION:
            cameras[activeCamera].processMouseMovement(event.motion.xrel, event.motion.yrel);
            break;
        }

        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                SDL_SetRelativeMouseMode(SDL_FALSE);
                break;
            case SDLK_w:
            case SDLK_s:
            case SDLK_a:
            case SDLK_d:
                inputHandler.setKeyDown(event.key.keysym.sym);
                break;
            }
        }
        else if (event.type == SDL_KEYUP)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_w:
            case SDLK_s:
            case SDLK_a:
            case SDLK_d:
                inputHandler.setKeyUp(event.key.keysym.sym);
                break;
            }
        }
    }

    void handleInput(float deltaTime)
    {
        CameraMovement direction = NONE;

        if (inputHandler.isKeyDown(SDLK_w))
            direction = FORWARD;
        if (inputHandler.isKeyDown(SDLK_s))
            direction = BACKWARD;
        if (inputHandler.isKeyDown(SDLK_a))
            direction = LEFT;
        if (inputHandler.isKeyDown(SDLK_d))
            direction = RIGHT;

        cameras[activeCamera].processKeyboard(direction, deltaTime);
    }

    void update(float deltaTime)
    {
        for (auto &model : models)
        {
            model.rotation.y += 10.f * deltaTime;
        }
    }

    void draw(Shader &modelShader)
    {
        for (auto &light : lights)
        {
            light.shader.use();
            light.updateWorldMatrix();
            light.bind(light.shader);
            cameras[activeCamera].bind(light.shader);
            light.draw(light.shader);
        }

        modelShader.use();

        // bind active camera
        cameras[activeCamera].bind(modelShader);

        // bind all lights (only one for now)
        for (auto &light : lights)
            light.bind(modelShader);

        // draw all models
        for (auto &model : models)
        {
            model.updateWorldMatrix();
            model.draw(modelShader);
        }
    }
};
