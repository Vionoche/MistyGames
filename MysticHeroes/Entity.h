#pragma once

#include <memory>
#include <vector>

#include "Component.h"

class Entity
{
public:
    int EntityId;
    std::string EntityName;
    std::vector<std::shared_ptr<Component>> Components;

    Entity(const int entityId, const char* entityName)
        : EntityId(entityId), EntityName(entityName)
    {
        std::cout << "Entity " << EntityName << " was created" << std::endl;
    }

    Entity(const Entity& other)
      : EntityId(other.EntityId), EntityName(other.EntityName)
    {
        std::cout << "Entity " << EntityName << " was copied" << std::endl;
    }

    ~Entity()
    {
        std::cout << "Entity " << EntityName << " was destroyed" << std::endl;
    }
};
