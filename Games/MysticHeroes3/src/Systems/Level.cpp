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
            const LevelGridItem gridItem = StaticLayer[row][col];

            if (gridItem.LevelTile.TileSetType == TileSetType::None)
            {
                continue;
            }

            float x = static_cast<float>(col);
            float y = -1.0f * static_cast<float>(row);

            _staticTileSet.Render(
                gridItem.LevelTile.Row,
                gridItem.LevelTile.Col,
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

std::vector<std::vector<LevelGridItem>> Level::MapToLevelGridItems(const std::vector<std::vector<LevelTile>>& levelTiles)
{
    std::vector<std::vector<LevelGridItem>> gridItems(levelTiles.size(), std::vector<LevelGridItem>(levelTiles[0].size()));

    for (auto row = 0; row < gridItems.size(); row++)
    {
        for (auto col = 0; col < gridItems[0].size(); col++)
        {
            gridItems[row][col] = { levelTiles[row][col] };
        }
    }

    return gridItems;
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