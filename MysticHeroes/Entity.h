#pragma once

#include <memory>
#include <vector>

#include "Component.h"

class Entity
{
public:
    int EntityId;
    const char* EntityName;
    std::vector<std::shared_ptr<Component>> Components;

    Entity(int entityId, const char* entityName)
        : EntityId(entityId), EntityName(entityName)
    {
    }
};
