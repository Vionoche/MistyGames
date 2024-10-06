#pragma once

#include <filesystem>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"
#include "Texture.h"

class Sprite
{
public:
    Sprite(const char* spriteImage);

    Sprite(const Sprite& other) = delete;

    void operator=(Sprite const&) = delete;

    ~Sprite();

    void Render(const glm::vec3& position, const glm::mat4& projection);

private:
    ShaderProgram* _shader = nullptr;
    Texture* _spriteImage = nullptr;

    unsigned int _vertexArray;
    unsigned int _vertexBuffer;
    unsigned int _elementBuffer;

    float _spriteWidth = 1.0f;
    float _spriteHeight = 1.0f;

    float _vertices[32] = {
        // positions         // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   3.0f / 6.0f, 6.0f / 7.0f,  // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   3.0f / 6.0f, 5.0f / 7.0f,         // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   2.0f / 6.0f, 5.0f / 7.0f,                // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   2.0f / 6.0f, 6.0f / 7.0f          // top left 
    };

    unsigned int _indices[6] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
};