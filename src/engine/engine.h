#pragma once

#include <optional>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../window.h"

#include "scenes/scene.h"

#include "managers/input.h"
#include "managers/resource.h"

#include "scenes/mesh.h"
#include "scenes/scene.h"

#include "nodes/camera.h"
#include "nodes/model.h"

using namespace std;

class Engine
{
private:
    // Window
    GLWindow window = GLWindow();

    // Managers
    InputHandler input = InputHandler();
    ResourceManager res = ResourceManager("");

    // Shaders
    optional<Shader> defaultShader;
    optional<Shader> lightShader;

    // Timings
    float deltaTime;
    float now;
    float lastFrame;

    // Scene controlling
    Scene currentScene = Scene();

public:
    Engine(const string &assetsDir)
    {
        res.assetsDir = assetsDir;
        defaultShader = res.getShader("default");
        lightShader = res.getShader("light");
    }

    void run()
    {

        glm::mat4 projection = glm::perspective(glm::radians(90.0f), window.getAspectRatio(), 0.1f, 100.0f);

        Camera camera = Camera(projection, glm::vec3(0.0f, 0.0f, -4.0f));

        Model backpack = res.getModel("backpack", true);

        float lastFrame = 0.0f;
        float deltaTime = 0.0f;
        float now = 0.0f;

        glm::vec3 lightPos = glm::vec3(0.f, 0.f, -4.f);
        glm::vec3 lightDirection = glm::vec3(0.f, 0.0f, -2.f);
        glm::vec3 lightAmbient = glm::vec3(0.2f);
        glm::vec3 lightDiffuse = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec3 lightSpecular = glm::vec3(1.0f, 1.0f, 1.0f);

        camera.turnTowards(backpack.position);

        Light light(lightAmbient, lightDiffuse, lightSpecular, lightDirection);
        light.position = lightPos;

        std::vector<Model> models{backpack};
        std::vector<Camera> cameras{camera};
        std::vector<Light> lights = {light};

        Scene scene(models, cameras, lights);

        loadScene(scene);

        bool quit = false;
        while (!quit)
        {
            now = SDL_GetTicks() / 1000.0f;
            deltaTime = now - lastFrame;
            lastFrame = now;

            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                    quit = true;
                currentScene.processSDLEvents(event);
            }

            if (currentScene.inputHandler.isKeyDown(SDLK_ESCAPE))
                quit = true;

            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            currentScene.handleInput(deltaTime);
            currentScene.update(deltaTime);

            if (defaultShader.has_value())
            {
                currentScene.draw(defaultShader.value());
            }

            // Swap the buffer
            window.swapBuffer();
        }

        window.close();
    }

    void loadScene(const Scene &scene)
    {
        currentScene = scene;
    }
};
