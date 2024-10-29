#pragma once

#include <vector>

#include "../Actors/MonsterFactory.h"
#include "../Assets/MonstersAssetUnits.h"
#include "../Assets/StaticAssetUnits.h"
#include "../Engine/FrameBox.h"
#include "../Systems/Level.h"

class Dungeon : public Level
{
public:
    Dungeon(
        TileSet& staticTileSet,
        TileSet& monstersTileSet,
        TileSet& roguesTileSet,
        FrameBox& frameBox,
        Player& player
    ) : Level(
        staticTileSet,
        monstersTileSet,
        roguesTileSet,
        frameBox,
        player
    )
    {
        StaticLayer = {
            {{ StoneBrickWallTop },    { StoneBrickWallSide1 },       { StoneBrickWallSide1 },       { StoneBrickWallSide1 },       { BlankFloorDarkGrey, true },  { StoneBrickWallSide1 },       { StoneBrickWallSide1 },       { StoneBrickWallSide1 },       { StoneBrickWallTop }},
            {{ StoneBrickWallTop },    { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { StoneBrickWallTop }},
            {{ StoneBrickWallTop },    { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { Bone1, true },               { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { StoneBrickWallTop }},
            {{ StoneBrickWallTop },    { BlankFloorDarkGrey, true },  { FloorStone2, true },         { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { StoneBrickWallTop }},
            {{ StoneBrickWallTop },    { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { FloorStone2, true },         { BlankFloorDarkGrey, true },  { StoneBrickWallTop }},
            {{ StoneBrickWallTop },    { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { Bone2, true },               { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { StoneBrickWallTop }},
            {{ StoneBrickWallTop },    { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { FloorStone1, true },         { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { BlankFloorDarkGrey, true },  { StoneBrickWallTop }},
            {{ StoneBrickWallSide1 },  { StoneBrickWallSide1 },       { StoneBrickWallSide1 },       { StoneBrickWallSide1 },       { StoneBrickWallSide1 },       { StoneBrickWallSide1 },       { StoneBrickWallSide1 },       { StoneBrickWallSide1 },       { StoneBrickWallSide1 }}
        };

        ActorsLayer = InitializeActorsLayer();

        AddActor(MonsterFactory::CreateSkeleton(), 1, 4);
        AddActor(MonsterFactory::CreateSkeleton(), 2, 2);
        AddActor(MonsterFactory::CreateSkeletonArcher(), 6, 6);

        SetPlayer(&player, 4, 2);
    }
};