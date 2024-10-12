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
    TileSetType TileSetType;
    int Row;
    int Col;
    bool IsGround;
};

const static LevelTile Empty = { TileSetType::None, 0, 0 };

class Level
{
public:
    std::vector<std::vector<LevelTile>> StaticLayer;
    std::vector<std::vector<LevelTile>> ActorsLayer;

    Level(TileSet& staticTileSet, FrameBox& frameBox)
        : _staticTileSet(staticTileSet), _frameBox(frameBox) {}

    void Render(const glm::mat4& projection, const bool showGrid);

protected:
    TileSet& _staticTileSet;
    FrameBox& _frameBox;
};

