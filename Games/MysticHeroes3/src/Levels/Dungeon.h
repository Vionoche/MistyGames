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
    Dungeon(TileSet& staticTileSet, TileSet& monstersTileSet, FrameBox& frameBox)
        : Level(staticTileSet, monstersTileSet, frameBox)
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
        AddActor(Skeleton, 1, 4);
        AddActor(Skeleton, 2, 2);
        AddActor(SkeletonArcher, 6, 6);

        //Actor actor = MonsterFactory::CreateSkeleton();
        Actor* actorPtr = new Monster;
        actorPtr->TileSetUnit = Skeleton;

        int xxx = 0;

        if (Monster* monster = dynamic_cast<Monster*>(actorPtr))
        {
            xxx++;
        }

        if (Player* player = dynamic_cast<Player*>(actorPtr))
        {
            xxx++;
        }

        delete actorPtr;
    }
};