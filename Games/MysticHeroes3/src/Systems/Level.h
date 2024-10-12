#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Engine//FrameBox.h"
#include "../Engine/TileSet.h"

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
    TileSetType TileSetType = None;
    int Row = 0;
    int Col = 0;
    bool IsGround = false;
};

const static LevelTile Empty = { TileSetType::None, 0, 0, false };

struct LevelGridItem
{
public:
    LevelTile LevelTile = Empty;
    bool IsMouseHovered = false;
};


class Level
{
public:
    std::vector<std::vector<LevelGridItem>> StaticLayer;
    std::vector<std::vector<LevelGridItem>> ActorsLayer;

    Level(TileSet& staticTileSet, FrameBox& frameBox)
        : _staticTileSet(staticTileSet), _frameBox(frameBox) {}

    void ProcessInput(const glm::vec2 mousePosition);

    void Render(const glm::mat4& projection, const bool showGrid);

protected:
    TileSet& _staticTileSet;
    FrameBox& _frameBox;

    std::vector<std::vector<LevelGridItem>> MapToLevelGridItems(const std::vector<std::vector<LevelTile>>& levelTiles);
};

