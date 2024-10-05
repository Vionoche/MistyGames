#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

class Texture
{
public:
    unsigned int TextureId;

    Texture(const char* texturePath, bool isRgba);
};