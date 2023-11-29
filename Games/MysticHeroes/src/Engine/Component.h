#pragma once

#include <iostream>

class Component
{
public:
    int EntityId;

    Component(int entityId) : EntityId(entityId)
    {
    }

    Component(const Component& other) = delete;

    void operator=(Component const&) = delete;

    void virtual PrintName() const
    {
        std::cout << "Base Component for EntityId = " << EntityId << std::endl;
    }

    virtual ~Component()
    {
        std::cout << "Component for EntityId = " << EntityId << " was destroyed" << std::endl;
    }
};