#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Engine/FrameBox.h"
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
    int TileSetRow = 0;
    int TileSetCol = 0;
    bool IsGround = false;
};

const static LevelTile EmptyLevelTile = { TileSetType::None, 0, 0, false };

struct StaticObject
{
public:
    LevelTile LevelTile = EmptyLevelTile;
    bool IsGround = false;
    bool IsMouseHovered = false;
};

enum ActorType
{
    Player,
    Monster
};

struct Actor
{
public:
    LevelTile LevelTile = EmptyLevelTile;
    ActorType ActorType = Player;
    bool IsMouseHovered = false;
};

struct PlayerPosition
{
public:
    int LevelRow = 0;
    int LevelCol = 0;
};

struct Player
{
public:
    PlayerPosition Position = { 0, 0 };
};

class Level
{
public:
    std::vector<std::vector<StaticObject>> StaticLayer;
    std::vector<std::vector<StaticObject>> ActorsLayer;

    Level(TileSet& staticTileSet, TileSet& monstersTileSet, FrameBox& frameBox)
        : _staticTileSet(staticTileSet), _monstersTileSet(monstersTileSet), _frameBox(frameBox) {}

    void ProcessInput(const glm::vec2 mousePosition);

    void Render(const glm::mat4& projection, const bool showGrid);

protected:
    TileSet& _staticTileSet;
    TileSet& _monstersTileSet;
    FrameBox& _frameBox;

    std::vector<std::vector<StaticObject>> MapToLevelGridItems(const std::vector<std::vector<LevelTile>>& levelTiles);

    std::vector<std::vector<StaticObject>> InitializeActorsLevel();

    void AddActor(LevelTile actor, int row, int col);

private:
    bool IsMouseHover(const int row, const int col, const glm::vec2 mousePosition);
};

