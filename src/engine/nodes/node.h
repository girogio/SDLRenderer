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
    std::vector<Node *> children;
    Node *parent;

    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;

    glm::mat4 localMatrix = glm::mat4(1.0f);
    glm::mat4 worldMatrix = glm::mat4(1.0f);
    glm::mat3 normalMatrix = glm::mat4(1.0f);

    Node() : position(glm::vec3(0.0f)), scale(glm::vec3(1.0f)), rotation(glm::vec3(0.0f)), parent(nullptr)
    {
    }

    Node(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation) : position(position), scale(glm::vec3(1.0f)), rotation(glm::vec3(0.0f)), parent(nullptr)
    {
        this->position = position;
        this->scale = scale;
        this->rotation = rotation;
    }

    // copy constructor

    Node(const Node &node)
    {
        this->name = node.name;
        this->position = node.position;
        this->scale = node.scale;
        this->rotation = node.rotation;
        this->parent = node.parent;
        this->localMatrix = node.localMatrix;
        this->worldMatrix = node.worldMatrix;
        this->normalMatrix = node.normalMatrix;
    }

    void removeChild(Node *child)
    {
        for (unsigned int i = 0; i < children.size(); i++)
        {
            if (children[i] == child)
            {
                children.erase(children.begin() + i);
                return;
            }
        }
    }

    void setParent(Node *parent)
    {
        if (this->parent != nullptr)
        {
            this->parent->removeChild(this);
        }

        this->parent = parent;
        parent->children.push_back(this);
    }

    auto computeLocalMatrix()
    {
        glm::mat4 identity = glm::mat4(1.0f);

        identity = glm::translate(identity, position);
        identity = glm::scale(identity, scale);
        identity = glm::rotate(identity, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        identity = glm::rotate(identity, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        identity = glm::rotate(identity, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

        this->localMatrix = identity;

        return localMatrix;
    }

    void updateWorldMatrix(glm::mat4 *parentWorldMatrix)
    {
        computeLocalMatrix();

        normalMatrix = glm::mat3(glm::transpose(glm::inverse(worldMatrix)));

        if (parentWorldMatrix != nullptr)
            worldMatrix = *parentWorldMatrix * localMatrix;
        else
            worldMatrix = localMatrix;

        for (unsigned int i = 0; i < children.size(); i++)
            children[i]->updateWorldMatrix(&worldMatrix);
    }

    void updateWorldMatrix()
    {
        updateWorldMatrix(nullptr);
    }

    glm::mat4 getModelMatrix()
    {
        return worldMatrix;
    }
};
