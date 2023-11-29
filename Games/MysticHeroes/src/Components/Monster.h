#pragma once

#include "../Engine/Component.h"

class Monster : public Component
{
public:
    Monster(int entityId) : Component(entityId)
    {
    }
};