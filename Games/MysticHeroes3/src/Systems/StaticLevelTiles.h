#pragma once

#include "Level.h"

const static LevelTile DirtWallTop = { TileSetType::Static, 23, 0 };
const static LevelTile DirtWallSide = { TileSetType::Static, 23, 1 };
const static LevelTile InnerWall = { TileSetType::Static, 23, 2 };

const static LevelTile RoughStoneWallTop = { TileSetType::Static, 22, 0 };
const static LevelTile RoughStoneWallSide = { TileSetType::Static, 22, 1 };

const static LevelTile StoneBrickWallTop = { TileSetType::Static, 21, 0 };
const static LevelTile StoneBrickWallSide1 = { TileSetType::Static, 21, 1 };
const static LevelTile StoneBrickWallSide2 = { TileSetType::Static, 21, 2 };

const static LevelTile BlankFloorDarkGrey = { TileSetType::Static, 17, 0, true };
const static LevelTile FloorStone1 = { TileSetType::Static, 17, 1, true };
const static LevelTile FloorStone2 = { TileSetType::Static, 17, 2, true };

const static LevelTile BlankFloorDarkPurple = { TileSetType::Static, 16, 0, true };
const static LevelTile Grass1 = { TileSetType::Static, 16, 1, true };
const static LevelTile Grass2 = { TileSetType::Static, 16, 2, true };
const static LevelTile Grass3 = { TileSetType::Static, 16, 3, true };

const static LevelTile StoneFloor1 = { TileSetType::Static, 14, 1, true };
const static LevelTile StoneFloor2 = { TileSetType::Static, 14, 2, true };
const static LevelTile StoneFloor3 = { TileSetType::Static, 14, 3, true };

const static LevelTile Bone1 = { TileSetType::Static, 13, 1, true };
const static LevelTile Bone2 = { TileSetType::Static, 13, 2, true };
const static LevelTile Bone3 = { TileSetType::Static, 13, 3, true };