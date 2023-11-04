#pragma once
#include "Monster.h"

class Goblin : public Monster
{
public:
    Goblin(int monsterId)
        : Monster(monsterId, "Goblin", 20, 0.0f, 0.0f, 20)
    {
    }
};