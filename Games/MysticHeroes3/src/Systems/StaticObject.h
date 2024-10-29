#pragma once

#include "../Assets/TileSetUnit.h"

class StaticObject
{
public:
    StaticObject(TileSetUnit tileSetUnit)
    {
        TileSetUnit = tileSetUnit;
        IsGround = false;
    }

    StaticObject(TileSetUnit tileSetUnit, bool isGround)
    {
        TileSetUnit = tileSetUnit;
        IsGround = isGround;
    }

    TileSetUnit TileSetUnit;
    bool IsGround;
    bool IsMouseHovered = false;
};