#pragma once

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../window.h";

#include "scenes/scene.h"
#include "managers/resource.h";

class Engine
{
private:
    // Window
    GLWindow window = GLWindow();

    // Managers
    ResourceManager res;
    InputHandler input;

    // Shaders
    Shader defaultShader;

    // Timings
    float deltaTime;
    float now;
    float lastFrame;

    // Scene controlling
    Scene currentScene;

public:
    Engine(const std::string &assetsRootPath)
    {
        // this->res = ResourceManager(assetsRootPath);
    }

    void run()

    {
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

            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            //     currentScene.handleInput(deltaTime);
            //     scene.update(deltaTime);
            //     scene.draw(defaultShader);

            //     frames++;
            //     fpsCounter += deltaTime;
            //     if (fpsCounter >= FPS_INTERVAL)
            //     {
            //         fps = frames / fpsCounter;
            //         std::cout << "FPS: " << fps << std::endl;
            //         frames = 0;
            //         fpsCounter = 0.0f;
            //     }

            //     // Swap the buffer
            //     window.swapBuffer();
            // }

            // window.close();
        }
    };
