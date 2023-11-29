#pragma once

#include <memory>
#include <vector>

#include "Component.h"

class Component;

class Entity
{
public:
    int EntityId;
    std::string EntityName;
    std::vector<std::shared_ptr<Component>> Components;

    Entity(const int entityId, const char* entityName)
        : EntityId(entityId), EntityName(entityName)
    {
    }

    Entity(const Entity& other) = delete;

    void operator=(Entity const&) = delete;
};
