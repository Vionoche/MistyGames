#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Assets/TileSetUnit.h"
#include "../Engine/FrameBox.h"
#include "../Engine/TileSet.h"
#include "Actor.h"
#include "StaticObject.h"

class Level
{
public:
    std::vector<std::vector<StaticObject>> StaticLayer;
    std::vector<std::vector<Actor*>> ActorsLayer;

    Level(TileSet& staticTileSet, TileSet& monstersTileSet, FrameBox& frameBox)
        : _staticTileSet(staticTileSet), _monstersTileSet(monstersTileSet), _frameBox(frameBox) {}

    void ProcessInput(const glm::vec2 mousePosition);

    void Render(const glm::mat4& projection, const bool showGrid);

    ~Level();

protected:
    TileSet& _staticTileSet;
    TileSet& _monstersTileSet;
    FrameBox& _frameBox;

    std::vector<std::vector<Actor*>> InitializeActorsLayer();

    void AddActor(Actor* actor, int row, int col);

private:
    bool IsMouseHover(const int row, const int col, const glm::vec2 mousePosition);
};

