cmake_minimum_required(VERSION 3.28)
project(SDLRenderer)

set(CMAKE_CXX_STANDARD 23)

  set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS )
set(CMAKE_CXX_FLAGS_RELEASE "/O2")

add_executable(SDLRenderer src/main.cpp lib/stb_image.cpp)

target_include_directories(SDLRenderer PRIVATE lib)

find_package(OpenGL REQUIRED)
target_link_libraries(SDLRenderer PRIVATE ${OPENGL_LIBRARIES})
target_include_directories(SDLRenderer PRIVATE ${OPENGL_INCLUDE_DIR})

find_package(SDL2 CONFIG REQUIRED)
target_include_directories(SDLRenderer PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(SDLRenderer
        PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
)

find_package(GLEW REQUIRED)
target_link_libraries(SDLRenderer PRIVATE GLEW::GLEW)

find_package(glm CONFIG REQUIRED)
target_link_libraries(SDLRenderer PRIVATE glm::glm)

find_package(assimp CONFIG REQUIRED)
target_link_libraries(SDLRenderer PRIVATE assimp::assimp)

find_package(OpenAL CONFIG REQUIRED)
target_link_libraries(SDLRenderer PRIVATE OpenAL::OpenAL)
