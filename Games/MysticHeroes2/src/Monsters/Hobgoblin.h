#pragma once
#include "Monster.h"

class Hobgoblin : public Monster
{
public:
    Hobgoblin(int monsterId)
        : Monster(monsterId, "Hobgoblin", 30, 0.0f, 0.0f, 50)
    {
    }
};