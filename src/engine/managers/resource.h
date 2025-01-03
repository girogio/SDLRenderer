#pragma once

#include <string>
#include <filesystem>

#include "../shader.h"

const char *textureDir = "textures";
const char *modelDir = "models";
const char *shaderDir = "shaders";
const char *audioDir = "audio";

class ResourceManager
{
public:
    std::filesystem::path assetsDir;

    ResourceManager(const std::string &basePath) : assetsDir(basePath) {}

    ~ResourceManager() {};

    auto getShader(const std::string shaderName)
    {
        const auto vertexPath = getShaderPath(shaderName + ".vs").string();
        const auto fragmentPath = getShaderPath(shaderName + ".fs").string();

        return Shader(vertexPath, fragmentPath);
    }

    auto getModel(const std::string modelName, bool gamma = false)
    {
        const auto modelPath = getModelPath(modelName + "/" + modelName + ".obj").string();
        return Model(modelPath, gamma);
    }

    std::filesystem::path getTexturePath(const std::string textureName)
    {
        return (assetsDir / textureDir / textureName).string();
    }

    std::filesystem::path getModelPath(const std::string modelName)
    {
        return assetsDir / modelDir / modelName;
    }

    std::filesystem::path getShaderPath(const std::string shaderName)
    {
        return assetsDir / shaderDir / shaderName;
    }

    std::filesystem::path getAudioPath(const std::string audioName)
    {

        return assetsDir / audioDir / audioName;
    }
};
