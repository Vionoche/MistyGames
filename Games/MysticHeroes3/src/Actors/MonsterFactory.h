#pragma once

#include <iostream>

#include "../Assets/MonstersAssetUnits.h"
#include "../Systems/Actor.h"

class MonsterFactory
{
public:
    static Actor CreateSkeleton()
    {
        Monster m;
        m.TileSetUnit = Skeleton;
        m.Class = MonsterClass::SkeletonClass;

        return std::move(m);
    }

    static Actor CreateSkeletonArcher()
    {
        Monster m;
        m.TileSetUnit = Skeleton;
        m.Class = MonsterClass::SkeletonArcherClass;

        return std::move(m);
    }
};