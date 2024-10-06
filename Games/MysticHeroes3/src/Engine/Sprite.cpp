#include "Sprite.h"

Sprite::Sprite(const char* spriteImage)
{
    // Shader
    const auto currentPath = std::filesystem::current_path();
    const auto textureVertexPath = currentPath / "shaders" / "sprite.vert";
    const auto textureFragmentPath = currentPath / "shaders" / "sprite.frag";

    _shader = new ShaderProgram(textureVertexPath.string().c_str(), textureFragmentPath.string().c_str());
    _shader->Use();
    _shader->SetInt("spriteImage", 0);

    _spriteImage = new Texture(spriteImage, true);

    // Vertex Array
    glGenVertexArrays(1, &_vertexArray);
    glBindVertexArray(_vertexArray);

    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &_elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);

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

Sprite::~Sprite()
{
    delete _shader;
    delete _spriteImage;

    glDeleteVertexArrays(1, &_vertexArray);
    glDeleteBuffers(1, &_vertexBuffer);
    glDeleteBuffers(1, &_elementBuffer);
}

void Sprite::Render(const glm::vec3& position, const glm::mat4& projection)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _spriteImage->TextureId);

    // Transform
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, position);
    transform = glm::scale(transform, glm::vec3(_spriteWidth, _spriteHeight, 1.0));

    _shader->Use();
    _shader->SetMat4("projection", projection);
    _shader->SetMat4("transform", transform);

    glBindVertexArray(_vertexArray);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}