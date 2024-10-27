#pragma once

enum TileSetAsset
{
    None,
    Static,
    Rogues,
    Monsters
};

struct TileSetUnit
{
public:
    TileSetAsset Asset = TileSetAsset::None;
    int AssetRow = 0;
    int AssetCol = 0;
    bool IsGround = false;
};

const static TileSetUnit EmptyTileSetUnit = { TileSetAsset::None, 0, 0, false };
