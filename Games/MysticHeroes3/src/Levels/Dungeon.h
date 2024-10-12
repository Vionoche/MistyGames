#pragma once

#include <vector>

#include "../Engine/FrameBox.h"
#include "../Systems/Level.h"
#include "../Systems/StaticLevelTiles.h"

class Dungeon : public Level
{
public:
    Dungeon(TileSet& staticTileSet, FrameBox& frameBox)
        : Level(staticTileSet, frameBox)
    {
        StaticLayer = MapToLevelGridItems({
            {{ StoneBrickWallTop },   { StoneBrickWallSide1 }, { StoneBrickWallSide1 }, { StoneBrickWallSide1 }, { BlankFloorDarkGrey },  { StoneBrickWallSide1 }, { StoneBrickWallSide1 }, { StoneBrickWallSide1 }, { StoneBrickWallTop }},
            {{ StoneBrickWallTop },   { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { StoneBrickWallTop }},
            {{ StoneBrickWallTop },   { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { Bone1 },               { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { StoneBrickWallTop }},
            {{ StoneBrickWallTop },   { BlankFloorDarkGrey },  { FloorStone2 },         { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { StoneBrickWallTop }},
            {{ StoneBrickWallTop },   { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { FloorStone2 },         { BlankFloorDarkGrey },  { StoneBrickWallTop }},
            {{ StoneBrickWallTop },   { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { Bone2 },               { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { StoneBrickWallTop }},
            {{ StoneBrickWallTop },   { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { FloorStone1 },         { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { BlankFloorDarkGrey },  { StoneBrickWallTop }},
            {{ StoneBrickWallSide1 }, { StoneBrickWallSide1 }, { StoneBrickWallSide1 }, { StoneBrickWallSide1 }, { StoneBrickWallSide1 }, { StoneBrickWallSide1 }, { StoneBrickWallSide1 }, { StoneBrickWallSide1 }, { StoneBrickWallSide1 }}
        });
    }
};