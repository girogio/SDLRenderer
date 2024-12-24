#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "window.h"

#include "engine/managers/input.h"
#include "engine/scenes/camera.h"
#include "engine/scenes/scene.h"
#include "engine/shader.h"

#include "engine/scenes/mesh.h"
#include "engine/scenes/model.h"

#define FPS_INTERVAL 1.0

int main(int argc, char *argv[])
{
    GLWindow window = GLWindow();

    InputHandler inputHandler = InputHandler();

    Shader defaultShader("../src/assets/shaders/default.vs", "../src/assets/shaders/default.fs");
    Shader lightShader("../src/assets/shaders/light.vs", "../src/assets/shaders/light.fs");

    glm::mat4 projection = glm::perspective(glm::radians(90.0f), window.getAspectRatio(), 0.1f, 100.0f);

    Camera camera = Camera(projection, glm::vec3(0.0f, 0.0f, -4.0f));

    Model backpack = Model("../src/assets/models/backpack/backpack.obj", false);

    float lastFrame = 0.0f;
    float deltaTime = 0.0f;
    float now = 0.0f;

    glm::vec3 lightPos = glm::vec3(0.f, 0.f, -4.f);
    glm::vec3 lightDirection = glm::vec3(0.f, 0.0f, -2.f);
    glm::vec3 lightAmbient = glm::vec3(0.1f, 0.1f, 0.1f);
    glm::vec3 lightDiffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 lightSpecular = glm::vec3(1.0f, 1.0f, 1.0f);

    camera.turnTowards(backpack.position);

    Light light = Light(lightAmbient, lightDiffuse, lightSpecular, lightDirection);
    light.position = lightPos;
    light.name = "light";
    light.m.name = "lightmodel";

    light.updateWorldMatrix();

    std::vector<Model> models{backpack};
    std::vector<Camera> cameras{camera};
    std::vector<Light> lights = {light};

    float fps = 0.0f;
    float fpsCounter = 0.0f;
    int frames = 0;

    Scene scene = Scene(models, cameras, lights);

    float bgColor[] = {0.1f, 0.1f, 0.1f, 1.0f};
    float gammaCorrection = 2.2f;

    float gammaCorrectedBgColor[3] = {
        pow(bgColor[0], gammaCorrection),
        pow(bgColor[1], gammaCorrection),
        pow(bgColor[2], gammaCorrection)};

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
            scene.processSDLEvents(event);
        }

        scene.handleInput(deltaTime);

        if (scene.inputHandler.isKeyDown(SDLK_ESCAPE))
            quit = true;

        glClearColor(gammaCorrectedBgColor[0], gammaCorrectedBgColor[1], gammaCorrectedBgColor[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.update(deltaTime);

        scene.draw(defaultShader);

        // fps counter
        frames++;
        fpsCounter += deltaTime;
        if (fpsCounter >= FPS_INTERVAL)
        {
            fps = frames / fpsCounter;
            std::cout << "FPS: " << fps << std::endl;
            frames = 0;
            fpsCounter = 0.0f;
        }

        // Swap the buffer
        window.swapBuffer();
    }

    window.close();

    return 0;
}
