#pragma once

#include <vector>

enum TileSetType
{
    None,
    Static,
    Rogues,
    Monsters
};

struct LevelTile
{
public:
    TileSetType TileSetType;
    int Row;
    int Col;
};

class Level
{
public:
    int Rows;
    int Cols;
    std::vector<std::vector<LevelTile>> StaticLayer;
    std::vector<std::vector<LevelTile>> ActorsLayer;
};

