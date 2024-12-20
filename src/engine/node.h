#pragma once

#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Node
{
public:
    unsigned int id;
    std::string name;
    std::vector<Node> children;
    Node *parent;

    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;

    Node() : position(glm::vec3(0.0f)), scale(glm::vec3(1.0f)), rotation(glm::vec3(0.0f)), parent(nullptr)
    {
    }

    Node(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation) : position(position), scale(glm::vec3(1.0f)), rotation(glm::vec3(0.0f)), parent(nullptr)
    {
        std::cout << "Node created" << std::endl;

        this->position = position;
        this->scale = scale;
        this->rotation = rotation;
        this->parent = nullptr;
    }

    ~Node()
    {
        // std::cout << "Node destroyed" << std::endl;
    }

    void setParent(Node *parent)
    {
        this->parent = parent;
        parent->children.push_back(*this);
    }

    glm::mat4 getModelMatrix()
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::scale(model, scale);
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

        return model;
    }
};
