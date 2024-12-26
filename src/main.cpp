#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "window.h"

#include "engine/shader.h"

#include "engine/managers/input.h"

#include "engine/scenes/mesh.h"
#include "engine/scenes/scene.h"

#include "engine/nodes/camera.h"
#include "engine/nodes/model.h"

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
    // backpack.scale = glm::vec3(1f);

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

    // unsigned int FBO;
    // glGenFramebuffers(1, &FBO);
    // glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    // unsigned int textureColorbuffer;
    // glGenTextures(1, &textureColorbuffer);
    // glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window.width, window.height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

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

        if (scene.inputHandler.isKeyDown(SDLK_ESCAPE))
            quit = true;

        glClearColor(gammaCorrectedBgColor[0], gammaCorrectedBgColor[1], gammaCorrectedBgColor[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        scene.handleInput(deltaTime);
        scene.update(deltaTime);
        scene.draw(defaultShader);

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
