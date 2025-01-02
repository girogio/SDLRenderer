#pragma once

#include <string>

const char *textureDir = "textures";
const char *modelDir = "models";
const char *shaderDir = "shaders";
const char *audioDir = "audio";

class ResourceManager
{
public:
    std::string assetsDir;

    ResourceManager(const std::string &basePath)
    {
        if (basePath.back() == '/')
        {
            this->assetsDir = basePath.substr(0, basePath.length() - 1);
        }
        else
        {
            this->assetsDir = basePath;
        }
    }

    std::string getTexturePath(const std::string textureName)
    {
        return assetsDir + "/" + textureDir + "/" + textureName;
    }

    std::string getModelPath(const std::string modelName)
    {
        return assetsDir + "/" + modelDir + "/" + modelName;
    }

    std::string getShaderPath(const std::string shaderName)
    {
        return assetsDir + "/" + shaderDir + "/" + shaderName;
    }

    std::string getAudioPath(const std::string audioName)
    {

        return assetsDir + "/" + audioDir + "/" + audioName;
    }

    ~ResourceManager() {}
};
