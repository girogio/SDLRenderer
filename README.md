# SDLRenderer

A cross-platform 3D multipurpose graphics / audio engine using SDL2, OpenGL and OpenAL.

## Dependencies

### Linux (Debian/Ubuntu)

```bash
sudo apt-get install libsdl2-dev libglew-dev libglm-dev libassimp-dev libopenal-dev libsndfile1-dev
```

### macOS

```bash
brew install glew glm assimp openal-soft libsndfile
```

## Windows

```powershell
vcpkg integrate install
vcpkg add port sdl2  glew glm assimp openal-soft libsndfile
vcpkg install
```
