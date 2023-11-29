#pragma once

#include "../Engine/Component.h"

#include <ostream>


class Health : public Component
{
public:
    int HealthPoints;
    float PhysicalResist;
    float MagicResist;

    Health(
        int entityId,
        int healthPoints,
        float physicalResist,
        float magicResist)
        : Component(entityId), HealthPoints(healthPoints), PhysicalResist(physicalResist), MagicResist(magicResist)
    {
    }

    void PrintName() const override
    {
        std::cout << "Health Component EntityId = " << EntityId << std::endl;
    }
};
