#include "FrameBox.h"

FrameBox::FrameBox()
{
    // Shader
    const auto currentPath = std::filesystem::current_path();
    const auto vertexPath = currentPath / "shaders" / "frame_box.vert";
    const auto fragmentPath = currentPath / "shaders" / "frame_box.frag";

    _shader = new ShaderProgram(vertexPath.string().c_str(), fragmentPath.string().c_str());
    _shader->Use();
}

FrameBox::~FrameBox()
{
    delete _shader;
}

void FrameBox::Render(const glm::vec4& color, const glm::vec3& position, const glm::mat4& projection)
{
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, position);
    transform = glm::scale(transform, glm::vec3(_width, _height, 1.0));

    _shader->Use();
    _shader->SetVec4("color", color);
    _shader->SetMat4("projection", projection);
    _shader->SetMat4("transform", transform);

    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
    glEnd();
}