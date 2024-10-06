#pragma once

#include <filesystem>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"
#include "Texture.h"

struct Tile
{
public:
    unsigned int VertexArray;
    unsigned int VertexBuffer;
    unsigned int ElementBuffer;
};

class TileSet
{
public:
    TileSet(const char* tileSetImage, int rows, int cols);

    TileSet(const TileSet& other) = delete;

    void operator=(TileSet const&) = delete;

    ~TileSet();

    void Render(int row, int col, const glm::vec3& position, const glm::mat4& projection);

private:
    ShaderProgram* _shader = nullptr;
    Texture* _tilesImage = nullptr;
    Tile*** _tiles = nullptr;

    int _rows;
    int _cols;

    const float _spriteWidth = 1.0f;
    const float _spriteHeight = 1.0f;

    const float _baseVertices[32] = {
        // positions         // colors           // texture coords
        0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    const unsigned int _baseIndices[6] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
};