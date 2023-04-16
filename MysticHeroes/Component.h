#pragma once

#include <iostream>

class Component
{
public:
    int EntityId;

    Component(int entityId) : EntityId(entityId)
    {
    }

    Component(const Component& other) : EntityId(other.EntityId)
    {
        std::cout << "Component " << EntityId << " was copied" << std::endl;
    }

    void virtual PrintName() const
    {
        std::cout << "Base Component EntityId = " << EntityId << std::endl;
    }

    virtual ~Component() = default;
};
