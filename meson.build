project(
    'SDLRender',
    'cpp',
    default_options: [
        'default_library=static',
        'optimization=3',
    ],
)


# if windows
vcpkg = find_program('vcpkg', required : true)
run_command(vcpkg, 'install', '--x-wait-for-lock',
                              '--x-manifest-root=' + meson.current_source_dir())

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
