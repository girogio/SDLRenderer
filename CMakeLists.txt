cmake_minimum_required(VERSION 3.28)
project(SDLRender)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)
# optimization flags
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


add_executable(SDLRender src/main.cpp lib/stb_image.cpp)

target_include_directories(SDLRender PRIVATE lib)

find_package(OpenGL REQUIRED)
target_link_libraries(SDLRender PRIVATE ${OPENGL_LIBRARIES})
target_include_directories(SDLRender PRIVATE ${OPENGL_INCLUDE_DIR})

find_package(SDL2 CONFIG REQUIRED)
target_include_directories(SDLRender PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(SDLRender
        PRIVATE
        SDL2::SDL2-static
        SDL2::SDL2main
)

find_package(GLEW REQUIRED)
target_link_libraries(SDLRender PRIVATE GLEW::GLEW)

find_package(glm CONFIG REQUIRED)
target_link_libraries(SDLRender PRIVATE glm::glm)

find_package(assimp CONFIG REQUIRED)
target_link_libraries(SDLRender PRIVATE assimp::assimp)

find_package(OpenAL CONFIG REQUIRED)
target_link_libraries(SDLRender PRIVATE OpenAL::OpenAL)
