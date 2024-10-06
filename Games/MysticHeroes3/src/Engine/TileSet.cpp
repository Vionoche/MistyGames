#include "TileSet.h"

TileSet::TileSet(const char* tileSetImage, int rows, int cols)
{
    // Shader
    const auto currentPath = std::filesystem::current_path();
    const auto textureVertexPath = currentPath / "shaders" / "sprite.vert";
    const auto textureFragmentPath = currentPath / "shaders" / "sprite.frag";

    _shader = new ShaderProgram(textureVertexPath.string().c_str(), textureFragmentPath.string().c_str());
    _shader->Use();
    _shader->SetInt("spriteImage", 0);

    _tilesImage = new Texture(tileSetImage, true);

    _rows = rows;
    _cols = cols;

    _tiles = new Tile**[_rows];

    for (auto row = 0; row < _rows; row++)
    {
        _tiles[row] = new Tile*[cols];

        for (auto col = 0; col < _cols; col++)
        {
            Tile* tile = new Tile{ 0, 0, 0 };

            _tiles[row][col] = tile;

            float tileVertices[32];

            memcpy(tileVertices, _baseVertices, sizeof(float) * 32);

            float textCoordX = static_cast<float>(col);
            float textCoordY = static_cast<float>(row);

            // top right
            tileVertices[6] = (textCoordX + 1.0f) / _cols;
            tileVertices[7] = (textCoordY + 1.0f) / _rows;

            // bottom right
            tileVertices[14] = (textCoordX + 1.0f) / _cols;
            tileVertices[15] = textCoordY / _rows;

            // bottom left
            tileVertices[22] = textCoordX / _cols;
            tileVertices[23] = textCoordY / _rows;

            // top left 
            tileVertices[30] = textCoordX / _cols;
            tileVertices[31] = (textCoordY + 1.0f) / _rows;

            // Vertex Array
            glGenVertexArrays(1, &tile->VertexArray);
            glBindVertexArray(tile->VertexArray);

            glGenBuffers(1, &tile->VertexBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, tile->VertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(tileVertices), tileVertices, GL_STATIC_DRAW);

            glGenBuffers(1, &tile->ElementBuffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tile->ElementBuffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_baseIndices), _baseIndices, GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            // color attribute
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            // texture coord attribute
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);
        }
    }
}

TileSet::~TileSet()
{
    delete _shader;
    delete _tilesImage;

    for (auto row = 0; row < _rows; row++)
    {
        for (auto col = 0; col < _cols; col++)
        {
            Tile* tile = _tiles[row][col];

            glDeleteVertexArrays(1, &tile->VertexArray);
            glDeleteBuffers(1, &tile->VertexBuffer);
            glDeleteBuffers(1, &tile->ElementBuffer);

            delete tile;
        }

        delete _tiles[row];
    }

    delete _tiles;
}

void TileSet::Render(int row, int col, const glm::vec3& position, const glm::mat4& projection)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _tilesImage->TextureId);

    // Transform
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, position);
    transform = glm::scale(transform, glm::vec3(_spriteWidth, _spriteHeight, 1.0));

    _shader->Use();
    _shader->SetMat4("projection", projection);
    _shader->SetMat4("transform", transform);

    Tile* tile = _tiles[row][col];
    glBindVertexArray(tile->VertexArray);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}