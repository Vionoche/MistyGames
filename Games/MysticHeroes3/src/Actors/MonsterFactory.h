#pragma once

#include <iostream>

#include "../Assets/MonstersAssetUnits.h"
#include "../Systems/Actor.h"

class MonsterFactory
{
public:
    static Actor* CreateSkeleton()
    {
        Monster* m = new Monster();
        m->TileSetUnit = Skeleton;
        m->Class = MonsterClass::SkeletonClass;

        return m;
    }

    static Actor* CreateSkeletonArcher()
    {
        Monster* m = new Monster();
        m->TileSetUnit = Skeleton;
        m->Class = MonsterClass::SkeletonArcherClass;

        return m;
    }
};