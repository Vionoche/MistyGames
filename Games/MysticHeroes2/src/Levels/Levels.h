#pragma once

#include "Level.h"
#include "../Monsters/Monsters.h"

class NewSorpigal : public Level
{
public:
    NewSorpigal()
        : Level(1, "New Sorpigal")
    {
        AddNode(new Goblin(++_globalId));
        AddNode(new Goblin(++_globalId));
        AddNode(new Goblin(++_globalId));
        AddNode(new Goblin(++_globalId));
        AddNode(new Hobgoblin(++_globalId));
        AddNode(new Hobgoblin(++_globalId));
    }
};


class GoblinWatch : public Level
{
public:
    GoblinWatch()
        : Level(2, "Goblin Watch Dungeon")
    {
        AddNode(new Goblin(++_globalId));
        AddNode(new Goblin(++_globalId));
        AddNode(new Goblin(++_globalId));
        AddNode(new Goblin(++_globalId));
        AddNode(new Hobgoblin(++_globalId));
        AddNode(new Hobgoblin(++_globalId));
        AddNode(new Skeleton(++_globalId));
    }
};


class SunkenTemple : public Level
{
public:
    SunkenTemple()
        : Level(3, "Sunken Temple Dungeon")
    {
        AddNode(new Hobgoblin(++_globalId));
        AddNode(new Hobgoblin(++_globalId));
        AddNode(new Hobgoblin(++_globalId));
        AddNode(new Skeleton(++_globalId));
        AddNode(new Skeleton(++_globalId));
        AddNode(new Skeleton(++_globalId));
    }
};