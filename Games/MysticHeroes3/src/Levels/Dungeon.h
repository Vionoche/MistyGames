#pragma once

#include <vector>

#include "../Assets/MonstersAssetUnits.h"
#include "../Assets/StaticAssetUnits.h"
#include "../Engine/FrameBox.h"
#include "../Systems/Level.h"

class Dungeon : public Level
{
public:
    Dungeon(TileSet& staticTileSet, TileSet& monstersTileSet, FrameBox& frameBox)
        : Level(staticTileSet, monstersTileSet, frameBox)
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

        ActorsLayer = InitializeActorsLevel();
        AddActor(Skeleton, 1, 4);
        AddActor(Skeleton, 2, 2);
        AddActor(SkeletonArcher, 6, 6);
    }
};