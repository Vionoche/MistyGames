#pragma once

#include "../Assets/MonstersAssetUnits.h"
#include "../Systems/Actor.h"

class MonsterFactory
{
public:
    static Monster* CreateSkeleton()
    {
        Monster* m = new Monster();
        m->TileSetUnit = Skeleton;
        m->Class = MonsterClass::SkeletonClass;

        return m;
    }

    static Monster* CreateSkeletonArcher()
    {
        Monster* m = new Monster();
        m->TileSetUnit = Skeleton;
        m->Class = MonsterClass::SkeletonArcherClass;

        return m;
    }
};