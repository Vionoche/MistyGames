#pragma once

#include <iostream>

class Component
{
public:
    int EntityId;

    Component() : EntityId(0)
    {
        std::cout << "Component " << EntityId << " was created" << std::endl;
    }

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

    void SetId(int entityId)
    {
        EntityId = entityId;
    }

    int GetId() const
    {
        return EntityId;
    }

    void virtual PrintName() const
    {
        std::cout << "Base Component EntityId = " << EntityId << std::endl;
    }
};
