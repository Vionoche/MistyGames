#pragma once

#include <iostream>

class Component
{
public:
    int EntityId;

    Component(int entityId) : EntityId(entityId)
    {
        std::cout << "Component " << EntityId << " was created" << std::endl;
    }

    Component(const Component& other) : EntityId(other.EntityId)
    {
        std::cout << "Component " << EntityId << " was copied" << std::endl;
    }

    virtual ~Component()
    {
        std::cout << "Component " << EntityId << " was destroyed" << std::endl;
    }

    void virtual PrintName() const
    {
        std::cout << "Base Component EntityId = " << EntityId << std::endl;
    }
};
