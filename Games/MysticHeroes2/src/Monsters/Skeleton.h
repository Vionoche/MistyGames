#pragma once
#include "Monster.h"

class Skeleton : public Monster
{
public:
    Skeleton(int monsterId)
        : Monster(monsterId, "Skeleton", 50, 0.5f, 0.5f, 100)
    {
    }
};