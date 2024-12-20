#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#define GL_VERSION_MAJOR 4
#define GL_VERSION_MINOR 3

#define MSAA_SAMPLES 4
#define DEPTH_SIZE 24
#define STENCIL_SIZE 8

class GLWindow
{
private:
    SDL_Window *window;
    SDL_GLContext context;

public:
    int width;
    int height;

    GLWindow(int width, int height) : width(width), height(height)
    {
        this->initWindow();
    }

    void initWindow()
    {

        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
            exit(-1);
        }

        // Set OpenGL version
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_VERSION_MAJOR);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_VERSION_MINOR);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, MSAA_SAMPLES);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, DEPTH_SIZE);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, STENCIL_SIZE);
#ifdef __APPLE__
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

        // lock mouse in window
        SDL_SetRelativeMouseMode(SDL_TRUE);

        // Create an SDL window and OpenGL context
        window = SDL_CreateWindow("SDLRenderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

        if (!window)
        {
            std::cerr << "SDL window creation failed: " << SDL_GetError() << std::endl;
            exit(-1);
        }

        context = SDL_GL_CreateContext(window);
        if (!context)
        {
            std::cerr << "SDL OpenGL context creation failed: " << SDL_GetError() << std::endl;
            exit(-1);
        }

        // Initialize GLEW
        glewExperimental = GL_TRUE; // Enable GLEW experimental features
        GLenum glewError = glewInit();
        if (glewError != GLEW_OK)
        {
            std::cerr << "GLEW initialization failed: " << glewGetErrorString(glewError) << std::endl;
            exit(-1);
        }

        // resize  callback
        SDL_AddEventWatch([](void *userdata, SDL_Event *event) -> int
                          {
                      if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_RESIZED)
                      {
                      glViewport(0, 0, event->window.data1, event->window.data2);
                      }
                      return 1; },
                          nullptr);

        // glEnable(GL_MULTISAMPLE);
    }

    void swapBuffer()
    {
        SDL_GL_SwapWindow(window);
    }

    void close()
    {
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    float getAspectRatio()
    {
        return (float)width / (float)height;
    }
};
