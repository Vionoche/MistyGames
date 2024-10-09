#pragma once

#include <vector>

#include "../Systems/Level.h"
#include "../Systems/StaticLevelTiles.h"

class Dungeon : public Level
{
    Dungeon()
    {
        Rows = 8;
        Cols = 13;

        StaticLayer = std::vector<std::vector<LevelTile>>(Rows, std::vector<LevelTile>(Cols));

        StaticLayer[0][0] = StoneBrickWallTop;
    }
};