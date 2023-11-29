#pragma once

#include "../Engine/Component.h"

class TakenDamage : public Component
{
public:
    uint32_t PhysicalDamage;
    uint32_t MagicDamage;

    TakenDamage(int entityId, uint32_t physicalDamage, uint32_t magicDamage)
        : Component(entityId), PhysicalDamage(physicalDamage), MagicDamage(magicDamage)
    {
    }
};