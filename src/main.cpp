#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "window.h"

#include "engine/input.h"
#include "engine/camera.h"
#include "engine/shader.h"

#include "engine/mesh.h"
#include "engine/model.h"

void resizeCallback(int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(int argc, char *argv[])
{
    GLWindow window = GLWindow(SCREEN_WIDTH, SCREEN_HEIGHT);

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    InputHandler inputHandler = InputHandler();

    std::vector<unsigned int> indices;

    std::vector<Vertex> vertices = {
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}};

    indices = {
        0, 1, 2, 2, 3, 0,
        1, 5, 6, 6, 2, 1,
        7, 6, 5, 5, 4, 7,
        4, 0, 3, 3, 7, 4,
        4, 5, 1, 1, 0, 4,
        3, 2, 6, 6, 7, 3};

    Shader defaultShader("../src/engine/shaders/default.vs", "../src/engine/shaders/default.fs");

    defaultShader.use();

    float xOffset = 0.0f;
    float lastFrame = 0.0f;
    float deltaTime = 0.0f;
    float now = 0.0f;

    // load texture
    Texture t = TextureFromFile("wall.png", "../src/assets/textures/", true);

    Mesh triangle = Mesh(vertices, indices, std::vector<Texture>({t}));
    glm::mat4 model = glm::mat4(1.0f);
    defaultShader.setMat4("model", model);

    // Model backpack = Model("../src/assets/models/backpack/backpack.obj", false);
    // defaultShader.setMat4("model", backpack.getModelMatrix());

    Camera c = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    glm::mat4 view = c.getViewMatrix();

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(c.zoom), window.getAspectRatio(), 0.1f, 1000.0f);

    defaultShader.setMat4("view", view);
    defaultShader.setMat4("projection", projection);

    bool invertPitch = true;

    // Main loop
    bool quit = false;
    while (!quit)
    {
        // Calculate delta time
        now = SDL_GetTicks() / 1000.0f;
        deltaTime = now - lastFrame;
        lastFrame = now;

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }

            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                resizeCallback(event.window.data1, event.window.data2);
            }

            if (event.type == SDL_MOUSEMOTION && SDL_GetRelativeMouseMode())
            {
                c.processMouseMovement(event.motion.xrel, event.motion.yrel * (invertPitch ? -1 : 1));
            }

            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                SDL_SetRelativeMouseMode(SDL_TRUE);
            }

            if (event.type == SDL_MOUSEWHEEL)
            {
                c.processMouseScroll(event.wheel.y);
                projection = glm::perspective(glm::radians(c.zoom), window.getAspectRatio(), 0.1f, 100.0f);
                defaultShader.setMat4("projection", projection);
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

        CameraMovement direction = NONE;

        if (inputHandler.isKeyDown(SDLK_w))
        {
            direction = FORWARD;
            c.processKeyboard(direction, deltaTime);
        }
        if (inputHandler.isKeyDown(SDLK_s))
        {
            direction = BACKWARD;
            c.processKeyboard(direction, deltaTime);
        }
        if (inputHandler.isKeyDown(SDLK_a))
        {
            direction = LEFT;
            c.processKeyboard(direction, deltaTime);
        }
        if (inputHandler.isKeyDown(SDLK_d))
        {
            direction = RIGHT;
            c.processKeyboard(direction, deltaTime);
        }

        defaultShader.setMat4("view", c.getViewMatrix());

        // Clear the screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw the triangle
        triangle.Draw(defaultShader);

        // backpack.Draw(defaultShader);

        // Swap the buffer
        window.swapBuffer();
    }

    window.close();

    return 0;
}
