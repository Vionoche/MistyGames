#include "Level.h"

void Level::ProcessInput(const glm::vec2 mousePosition)
{
    for (auto row = 0; row < StaticLayer.size(); row++)
    {
        for (auto col = 0; col < StaticLayer[0].size(); col++)
        {
            StaticLayer[row][col].IsMouseHovered = IsMouseHover(row, col, mousePosition);
        }
    }
}

void Level::Render(const glm::mat4& projection, const bool showGrid)
{
    bool isHovered = false;
    float hoveredX = 0.0f;
    float hoveredY = 0.0f;

    for (auto row = 0; row < StaticLayer.size(); row++)
    {
        for (auto col = 0; col < StaticLayer[0].size(); col++)
        {
            const StaticObject gridItem = StaticLayer[row][col];

            if (gridItem.LevelTile.Asset == TileSetAsset::None)
            {
                continue;
            }

            float x = static_cast<float>(col);
            float y = -1.0f * static_cast<float>(row);

            _staticTileSet.Render(
                gridItem.LevelTile.AssetRow,
                gridItem.LevelTile.AssetCol,
                glm::vec3(x, y, 0.0f),
                projection);

            if (showGrid && gridItem.LevelTile.IsGround && !gridItem.IsMouseHovered)
            {
                _frameBox.Render(
                    glm::vec4(0.0f, 0.5f, 0.2f, 1.0f),
                    glm::vec3(x, y, 0.0f),
                    projection);
            }

            if (gridItem.LevelTile.IsGround && gridItem.IsMouseHovered)
            {
                isHovered = true;
                hoveredX = x;
                hoveredY = y;
            }

            const StaticObject actor = ActorsLayer[row][col];

            if (actor.LevelTile.Asset != TileSetAsset::None)
            {
                _monstersTileSet.Render(
                    actor.LevelTile.AssetRow,
                    actor.LevelTile.AssetCol,
                    glm::vec3(x, y, 0.0f),
                    projection);
            }
        }
    }

    if (isHovered)
    {
        _frameBox.Render(
            glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
            glm::vec3(hoveredX, hoveredY, 0.0f),
            projection);
    }
}

std::vector<std::vector<StaticObject>> Level::MapToLevelGridItems(const std::vector<std::vector<TileSetUnit>>& levelTiles)
{
    std::vector<std::vector<StaticObject>> gridItems(levelTiles.size(), std::vector<StaticObject>(levelTiles[0].size()));

    for (auto row = 0; row < gridItems.size(); row++)
    {
        for (auto col = 0; col < gridItems[0].size(); col++)
        {
            gridItems[row][col] = { levelTiles[row][col] };
        }
    }

    return gridItems;
}

std::vector<std::vector<StaticObject>> Level::InitializeActorsLevel()
{
    std::vector<std::vector<StaticObject>> gridItems(StaticLayer.size(), std::vector<StaticObject>(StaticLayer[0].size(), { EmptyTileSetUnit, false }));

    return gridItems;
}

void Level::AddActor(TileSetUnit actor, int row, int col)
{
    ActorsLayer[row][col] = { actor, false };
}

bool Level::IsMouseHover(const int row, const int col, const glm::vec2 mousePosition)
{
    float x = static_cast<float>(col);
    float y = -1.0f * static_cast<float>(row);

    float left = x - 0.5f;
    float right = x + 0.5f;
    float top = y + 0.5f;
    float bottom = y - 0.5f;

    bool isHovered = mousePosition.x >= left && mousePosition.x <= right && mousePosition.y <= top && mousePosition.y >= bottom;

    return isHovered;
}