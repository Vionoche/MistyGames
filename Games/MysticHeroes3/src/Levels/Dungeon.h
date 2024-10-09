#pragma once

#include <vector>

#include "../Systems/Level.h"
#include "../Systems/StaticLevelTiles.h"

class Dungeon : public Level
{
public:
    Dungeon(TileSet& staticTileSet) : Level(staticTileSet)
    {
        StaticLayer = {
            {{ StoneBrickWallTop },   { StoneBrickWallSide1 }, { StoneBrickWallSide1 }, { StoneBrickWallSide1 }, { Empty },               { StoneBrickWallSide1 }, { StoneBrickWallSide1 }, { StoneBrickWallSide1 }, { StoneBrickWallTop }},
            {{ StoneBrickWallTop },   { Empty },               { Empty },               { Empty },               { Empty },               { Empty },               { Empty },               { Empty },               { StoneBrickWallTop }},
            {{ StoneBrickWallTop },   { Empty },               { Empty },               { Empty },               { Empty },               { Empty },               { Empty },               { Empty },               { StoneBrickWallTop }},
            {{ StoneBrickWallTop },   { Empty },               { Empty },               { Empty },               { Empty },               { Empty },               { Empty },               { Empty },               { StoneBrickWallTop }},
            {{ StoneBrickWallTop },   { Empty },               { Empty },               { Empty },               { Empty },               { Empty },               { Empty },               { Empty },               { StoneBrickWallTop }},
            {{ StoneBrickWallTop },   { Empty },               { Empty },               { Empty },               { Empty },               { Empty },               { Empty },               { Empty },               { StoneBrickWallTop }},
            {{ StoneBrickWallTop },   { Empty },               { Empty },               { Empty },               { Empty },               { Empty },               { Empty },               { Empty },               { StoneBrickWallTop }},
            {{ StoneBrickWallSide1 }, { StoneBrickWallSide1 }, { StoneBrickWallSide1 }, { StoneBrickWallSide1 }, { StoneBrickWallSide1 }, { StoneBrickWallSide1 }, { StoneBrickWallSide1 }, { StoneBrickWallSide1 }, { StoneBrickWallSide1 }}
        };
    }
};