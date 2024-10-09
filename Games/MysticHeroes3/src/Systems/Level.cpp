#include "Level.h"

void Level::Render(const glm::mat4& projection)
{
    for (auto row = 0; row < StaticLayer.size(); row++)
    {
        for (auto col = 0; col < StaticLayer[0].size(); col++)
        {
            if (StaticLayer[row][col].TileSetType == TileSetType::None)
            {
                continue;
            }

            float x = static_cast<float>(col);
            float y = -1.0f * static_cast<float>(row);

            _staticTileSet.Render(
                StaticLayer[row][col].Row,
                StaticLayer[row][col].Col,
                glm::vec3(x, y, 0.0f), projection);
        }
    }
}