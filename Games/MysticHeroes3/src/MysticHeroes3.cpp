#include <filesystem>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "Engine/MixedSprite.h"
#include "Engine/ShaderProgram.h"
#include "Engine/Texture.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
float windowWidth = 800.0f;
float windowHeight = 600.0f;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Player
float speed = 0.5f;
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

    // Create Sprite
    const auto currentPath = std::filesystem::current_path();
    const auto containerSpritePath = currentPath / "sprites" / "container.jpg";
    const auto awesomefaceSpritePath = currentPath / "sprites" / "awesomeface.png";

    MixedSprite sprite(containerSpritePath.string().c_str(), awesomefaceSpritePath.string().c_str());
    
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
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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

        glm::mat4 projection = glm::ortho(-scaleX, scaleX, -scaleY, scaleY, 0.0f, 1.0f);

        sprite.Render(glm::vec3(0.5f, -0.5f, 0.0f), projection);
        sprite.Render(glm::vec3(-0.5f, 0.5f, 0.0f), projection);

        // player
        sprite.Render(position, projection);

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
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    windowWidth = static_cast<float>(width);
    windowHeight = static_cast<float>(height);
}
