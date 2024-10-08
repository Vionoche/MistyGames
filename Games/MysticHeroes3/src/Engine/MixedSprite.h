#pragma once

#include <filesystem>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"
#include "Texture.h"

class MixedSprite
{
public:
    MixedSprite(const char* texturePath1, const char* texturePath2);

    MixedSprite(const MixedSprite& other) = delete;

    void operator=(MixedSprite const&) = delete;

    ~MixedSprite();

    void Render(const glm::vec3& position, const glm::mat4& projection);

private:
    ShaderProgram* _shader = nullptr;
    Texture* _texture1 = nullptr;
    Texture* _texture2 = nullptr;
    
    unsigned int _vertexArray;
    unsigned int _vertexBuffer;
    unsigned int _elementBuffer;

    float _spriteWidth = 1.0f;
    float _spriteHeight = 1.0f;

    float _vertices[32] = {
        // positions         // colors           // texture coords
        0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int _indices[6] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
};