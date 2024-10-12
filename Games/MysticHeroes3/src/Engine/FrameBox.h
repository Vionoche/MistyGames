#pragma once

#include <filesystem>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"

class FrameBox
{
public:
    FrameBox();

    FrameBox(const FrameBox& other) = delete;

    void operator=(FrameBox const&) = delete;

    ~FrameBox();

    void Render(const glm::vec3& position, const glm::mat4& projection);

private:
    ShaderProgram* _shader = nullptr;

    const float _width = 1.0f;
    const float _height = 1.0f;
};