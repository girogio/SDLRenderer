project(
    'SDLRender',
    'cpp',
    default_options: [
        'default_library=static',
        'cpp_std=c++23',
        'optimization=3',
    ],
)

sdl2_dep = dependency('sdl2')
glew_dep = dependency('glew')
glm_dep = dependency('glm')
assimp_dep = dependency('assimp')
opengl_dep = dependency('opengl')

executable(
    meson.project_name(),
    ['src/main.cpp', 'lib/stb_image.cpp'],
    dependencies: [sdl2_dep, glew_dep, glm_dep, assimp_dep, opengl_dep],
    include_directories: 'lib',
)
