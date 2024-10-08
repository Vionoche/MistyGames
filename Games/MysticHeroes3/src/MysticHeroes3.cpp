#include <filesystem>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "Engine/ShaderProgram.h"
#include "Engine/Texture.h"
#include "Engine/TileSet.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Camera
float windowWidth = 800.0f;
float windowHeight = 600.0f;
float deltaX = 0.0f;
float deltaY = 0.0f;
float cameraSpeed = 0.5f;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Player
float speed = 1.0f;
glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(800, 600, "Mystic Heroes 3", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    stbi_set_flip_vertically_on_load(true);

    const auto currentPath = std::filesystem::current_path();

    // Create decorations
    const auto decorationsPath = currentPath / "sprites" / "tiles.png";
    TileSet decorationsTileSet(decorationsPath.string().c_str(), 24, 21);

    // Create monsters
    const auto monstersPath = currentPath / "sprites" / "monsters.png";
    TileSet monstersTileSet(monstersPath.string().c_str(), 13, 12);

    // Create Player
    const auto roguesPath = currentPath / "sprites" / "rogues.png";
    TileSet roguesTileSet(roguesPath.string().c_str(), 7, 6);
    
    while (!glfwWindowShouldClose(window))
    {
        const float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // logic
        // -----
        const float speed = 2.0f;
        const float velocity = speed * deltaTime;

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Projection
        float globalAspectRatio = windowWidth / windowHeight;
        float scaleX = 1.0f;
        float scaleY = 1.0f;

        if (globalAspectRatio > 1)
        {
            scaleX = globalAspectRatio;
        }
        else
        {
            scaleY = 1 / globalAspectRatio;
        }

        float cameraScale = 5.0f;
        glm::mat4 projection = glm::ortho((-scaleX + deltaX) * cameraScale, (scaleX + deltaX) * cameraScale, (-scaleY + deltaY) * cameraScale, (scaleY + deltaY) * cameraScale, 0.0f, 1.0f);

        // Level
        for (int i = 0; i < 11; i++)
        {
            if (i == 5)
            {
                continue;
            }
            decorationsTileSet.Render(22, 1, glm::vec3(-5.0f + static_cast<float>(i), 4.0f, 0.0f), projection);
        }
        decorationsTileSet.Render(7, 6, glm::vec3(0.0f, 4.0f, 0.0f), projection);
        for (int i = 0; i < 13; i++)
        {
            decorationsTileSet.Render(22, 1, glm::vec3(-6.0f + static_cast<float>(i), -4.0f, 0.0f), projection);
        }
        for (int i = 0; i < 8; i++)
        {
            decorationsTileSet.Render(22, 0, glm::vec3(-6.0f, 4.0f - static_cast<float>(i), 0.0f), projection);
            decorationsTileSet.Render(22, 0, glm::vec3(6.0f, 4.0f - static_cast<float>(i), 0.0f), projection);
        }

        decorationsTileSet.Render(6, 0, glm::vec3(-2.0f, 2.0f, 0.0f), projection);

        monstersTileSet.Render(8, 0, glm::vec3(2.0f, -2.0f, 0.0f), projection);
        monstersTileSet.Render(8, 0, glm::vec3(4.0f, -1.0f, 0.0f), projection);
        monstersTileSet.Render(8, 1, glm::vec3(5.0f, 2.0f, 0.0f), projection);

        // player
        roguesTileSet.Render(3, 1, position, projection);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        const float velocity = speed * deltaTime;
        position += glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        const float velocity = speed * deltaTime;
        position -= glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        const float velocity = speed * deltaTime;
        position -= glm::vec3(1.0f, 0.0f, 0.0f) * velocity;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        const float velocity = speed * deltaTime;
        position += glm::vec3(1.0f, 0.0f, 0.0f) * velocity;
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        const float velocity = cameraSpeed * deltaTime;
        deltaY += 1.0f * velocity;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        const float velocity = cameraSpeed * deltaTime;
        deltaY -= 1.0f * velocity;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        const float velocity = cameraSpeed * deltaTime;
        deltaX -= 1.0f * velocity;
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        const float velocity = cameraSpeed * deltaTime;
        deltaX += 1.0f * velocity;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    windowWidth = static_cast<float>(width);
    windowHeight = static_cast<float>(height);
}
