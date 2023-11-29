#pragma once

#include "../Engine/Component.h"

class Player : public Component
{
public:
    Player(int entityId) : Component(entityId)
    {
    }
};