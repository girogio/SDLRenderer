#define GL_VERSION_MAJOR 4
#define GL_VERSION_MINOR 1

#include <iostream>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#include <SDL.h>
#include <GL/glew.h>

#include "engine/shader.h"

void resizeCallback(int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Set OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_VERSION_MAJOR);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_VERSION_MINOR);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create an SDL window and OpenGL context
    SDL_Window *window = SDL_CreateWindow("SDLRenderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        std::cerr << "SDL window creation failed: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context)
    {
        std::cerr << "SDL OpenGL context creation failed: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Initialize GLEW
    glewExperimental = GL_TRUE; // Enable GLEW experimental features
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK)
    {
        std::cerr << "GLEW initialization failed: " << glewGetErrorString(glewError) << std::endl;
        return -1;
    }

    // resize  callback
    SDL_AddEventWatch([](void *userdata, SDL_Event *event) -> int
                      {
        if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_RESIZED)
        {
            resizeCallback(event->window.data1, event->window.data2);
        }
        return 1; },
                      nullptr);

    // Set up vertex data
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // Bottom left
        0.5f, -0.5f, 0.0f,  // Bottom right
        0.0f, 0.5f, 0.0f,   // Top
    };

    // Create VBO and VAO
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Shader defaultShader("../src/engine/shaders/default.vs", "../src/engine/shaders/default.fs");
    defaultShader.use();

    float xOffset = 0.0f;

    // Main loop
    bool quit = false;
    while (!quit)
    {

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    quit = true;
                }
            }
        }

        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the triangle
        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Swap the buffer
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
