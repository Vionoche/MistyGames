#pragma once
#include "Monster.h"


class Goblin : public Monster
{
public:
    Goblin(int monsterId)
        : Monster(monsterId, "Goblin", 20, 0.0f, 0.0f, 5, 0, 20)
    {
    }
};


class Hobgoblin : public Monster
{
public:
    Hobgoblin(int monsterId)
        : Monster(monsterId, "Hobgoblin", 30, 0.0f, 0.0f, 5, 3, 50)
    {
    }
};


class Skeleton : public Monster
{
public:
    Skeleton(int monsterId)
        : Monster(monsterId, "Skeleton", 50, 0.5f, 0.5f, 10, 10, 100)
    {
    }
};
