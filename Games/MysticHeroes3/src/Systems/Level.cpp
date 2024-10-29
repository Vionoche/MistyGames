#include "Level.h"

void Level::ProcessInput(const glm::vec2 mousePosition, const bool leftMouseButtonClicked)
{
    Position clickedPosition = { -1, -1 };

    for (auto row = 0; row < StaticLayer.size(); row++)
    {
        for (auto col = 0; col < StaticLayer[0].size(); col++)
        {
            StaticLayer[row][col].IsMouseHovered = IsMouseHover(row, col, mousePosition);

            if (leftMouseButtonClicked && StaticLayer[row][col].IsMouseHovered)
            {
                clickedPosition = { row, col };
            }
        }
    }

    if (leftMouseButtonClicked)
    {
        // Check ground
        if (!StaticLayer[clickedPosition.Row][clickedPosition.Col].IsGround)
        {
            return;
        }
        
        // Check player is nearby
        std::vector<Position> roundPositions;
        roundPositions.reserve(9);
        int counter = 0;
        int rowIndex = _playerPosition.Row - 1;
        int colIndex = _playerPosition.Col - 1;

        for (int index = 0; index < 9; index++)
        {
            bool isRowIndexInBoundary = rowIndex >= 0 && rowIndex < StaticLayer.size();
            bool isColIndexInBoundary = colIndex >= 0 && colIndex < StaticLayer[0].size();
            bool isPlayer = rowIndex == _playerPosition.Row && colIndex == _playerPosition.Col;

            if (isRowIndexInBoundary && isColIndexInBoundary && !isPlayer)
            {
                roundPositions.push_back({ rowIndex, colIndex });
            }

            colIndex++;

            if (colIndex > _playerPosition.Col + 1)
            {
                rowIndex++;
                colIndex = _playerPosition.Col - 1;
            }
        }

        bool isNearby = false;
        for (const auto& position : roundPositions)
        {
            if (clickedPosition.Row == position.Row && clickedPosition.Col == position.Col)
            {
                isNearby = true;
                break;
            }
        }

        if (!isNearby)
        {
            return;
        }

        // Check actors layer
        Actor* actor = ActorsLayer[clickedPosition.Row][clickedPosition.Col];
        if (actor != nullptr)
        {
            return;
        }

        // Move player if possible
        Actor* playerActor = ActorsLayer[_playerPosition.Row][_playerPosition.Col];
        Player* player = dynamic_cast<Player*>(playerActor);
        if (player != nullptr)
        {
            SetPlayer(player, clickedPosition.Row, clickedPosition.Col);
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

            if (gridItem.TileSetUnit.Asset == TileSetAsset::None)
            {
                continue;
            }

            float x = static_cast<float>(col);
            float y = -1.0f * static_cast<float>(row);

            _staticTileSet.Render(
                gridItem.TileSetUnit.AssetRow,
                gridItem.TileSetUnit.AssetCol,
                glm::vec3(x, y, 0.0f),
                projection);

            if (showGrid && gridItem.IsGround && !gridItem.IsMouseHovered)
            {
                _frameBox.Render(
                    glm::vec4(0.0f, 0.5f, 0.2f, 1.0f),
                    glm::vec3(x, y, 0.0f),
                    projection);
            }

            if (gridItem.IsGround && gridItem.IsMouseHovered)
            {
                isHovered = true;
                hoveredX = x;
                hoveredY = y;
            }

            Actor* actor = ActorsLayer[row][col];

            if (actor == nullptr || actor->TileSetUnit.Asset == TileSetAsset::None)
            {
                continue;
            }

            if (Monster* monster = dynamic_cast<Monster*>(actor))
            {
                _monstersTileSet.Render(
                    monster->TileSetUnit.AssetRow,
                    monster->TileSetUnit.AssetCol,
                    glm::vec3(x, y, 0.0f),
                    projection);
            }

            if (Player* player = dynamic_cast<Player*>(actor))
            {
                _roguesTileSet.Render(
                    player->TileSetUnit.AssetRow,
                    player->TileSetUnit.AssetCol,
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

Level::~Level()
{
    for (auto row = 0; row < ActorsLayer.size(); row++)
    {
        for (auto col = 0; col < ActorsLayer[0].size(); col++)
        {
            Actor* actor = ActorsLayer[row][col];
            Player* player = dynamic_cast<Player*>(actor);
            if (actor != nullptr && player == nullptr)
            {
                delete actor;
                ActorsLayer[row][col] = nullptr;
            }
        }
    }
}

std::vector<std::vector<Actor*>> Level::InitializeActorsLayer()
{
    std::vector<std::vector<Actor*>> actorLayer(StaticLayer.size(), std::vector<Actor*>(StaticLayer[0].size(), nullptr));
    return actorLayer;
}

void Level::AddActor(Actor* actor, int row, int col)
{
    ActorsLayer[row][col] = actor;
}

void Level::SetPlayer(Player* player, int row, int col)
{
    Actor* currentPlayerActor = ActorsLayer[row][col];

    if (currentPlayerActor != nullptr)
    {
        throw std::domain_error("Cannot place the player on the level grid. The place is not available.");
    }

    Actor* lastPlayerActor = ActorsLayer[_playerPosition.Row][_playerPosition.Col];
    Player* lastPlayer = dynamic_cast<Player*>(lastPlayerActor);
    if (lastPlayer != nullptr)
    {
        ActorsLayer[_playerPosition.Row][_playerPosition.Col] = nullptr;
    }

    _playerPosition = { row, col };
    ActorsLayer[_playerPosition.Row][_playerPosition.Col] = player;
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