#include "glm/glm.hpp"

#include "node.h"
#include "model.h"
#include "../shader.h"

#ifndef LIGHTTYPE
#define LIGHTTYPE
enum LightType
{
    DIRECTIONAL,
    POINT,
    SPOT
};
#endif

class Light : public Node
{
public:
    Shader shader = Shader("../src/assets/shaders/light.vs", "../src/assets/shaders/light.fs");
    Model m = Model("../src/assets/models/cube/cube.obj", false);

    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    std::string lightUniformName = "light";

    Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction)
        : ambient(ambient), diffuse(diffuse), specular(specular), direction(direction)
    {
        scale = glm::vec3(0.2f);
        m.setParent(this);
    }

    Light(const Light &light)
    {
        this->name = light.name;
        this->position = light.position;
        this->scale = light.scale;

        this->worldMatrix = light.worldMatrix;
        this->localMatrix = light.localMatrix;

        this->m.setParent(this);

        this->specular = light.specular;
        this->diffuse = light.diffuse;
        this->ambient = light.ambient;
        this->direction = light.direction;
    }

    void bind(Shader &shader)
    {
        shader.setVec3(lightUniformName + ".position", position);
        shader.setVec3(lightUniformName + ".direction", direction);

        shader.setMat3(lightUniformName + ".colours", glm::mat3(ambient, diffuse, specular));

        shader.setVec3(lightUniformName + ".const_lin_quad", glm::vec3(constant, linear, quadratic));
    }

    void draw(Shader &shader)
    {
        m.parent = this;
        m.draw(shader);
    }

    friend std::ostream &operator<<(std::ostream &os, const Light &light)
    {
        os << "Light name: " << light.name << std::endl;
        os << "Light position: " << light.position << std::endl;
        os << "Light direction: " << light.direction << std::endl;
        os << "scale: " << light.scale << std::endl;
        os << light.worldMatrix << std::endl;

        return os;
    }

    std::string generateShaderStruct()
    {
        return "struct Light\n"
               "{\n"
               "    vec3 position;\n"
               "    vec3 direction;\n"
               "    vec3 ambient;\n"
               "    vec3 diffuse;\n"
               "    vec3 specular;\n"
               "};\n";
    }
};
