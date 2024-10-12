#include <filesystem>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stb_image.h>

#include "Engine/FrameBox.h"
#include "Engine/ShaderProgram.h"
#include "Engine/Texture.h"
#include "Engine/TileSet.h"

#include "Systems/Level.h"

#include "Levels/Dungeon.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Camera
float windowWidth = 1024.0f;
float windowHeight = 800.0f;
float deltaX = 1.0f;
float deltaY = -0.8f;
float cameraSpeed = 0.5f;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Player
float speed = 1.0f;
glm::vec3 position = glm::vec3(4.0f, -3.0f, 0.0f);

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(1024, 800, "Mystic Heroes 3", nullptr, nullptr);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Image loading setup
    // ---------------------------------------
    stbi_set_flip_vertically_on_load(true);

    // Setup Dear ImGui context
    // ---------------------------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char* glsl_version = "#version 130";
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Setup sprites
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

    // Create FrameBox
    FrameBox box;

    // Create level
    Dungeon dungeon(decorationsTileSet);
    
    while (!glfwWindowShouldClose(window))
    {
        const float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Collect Debug Info
        // ------------------

        // Projection
        float globalAspectRatio = windowWidth / windowHeight;
        float scaleX = 1.0f;
        float scaleY = 1.0f;
        float cameraScale = 8.0f;

        if (globalAspectRatio > 1)
        {
            scaleX = globalAspectRatio;
        }
        else
        {
            scaleY = 1 / globalAspectRatio;
        }

        float orthoLeft = (-scaleX + deltaX) * cameraScale;
        float orthoRight = (scaleX + deltaX) * cameraScale;
        float orthoTop = (scaleY + deltaY) * cameraScale;
        float orthoBottom = (-scaleY + deltaY) * cameraScale;

        // Mouse Position
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float ndcMouseX = (mouseX / windowWidth) * 2.0f - 1.0f;
        float ndcMouseY = 1.0f - (mouseY / windowHeight) * 2.0f;

        float worldMouseX = (ndcMouseX + 1.0f) / 2.0f * (orthoRight - orthoLeft) + orthoLeft;
        float worldMouseY = (ndcMouseY + 1.0f) / 2.0f * (orthoTop - orthoBottom) + orthoBottom;

        // Render UI
        // ---------
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Debug Info");
        ImGui::Text("Cursor Position: X: %.3f Y: %.3f", worldMouseX, worldMouseY);
        ImGui::End();

        ImGui::Render();

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
        glm::mat4 projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, 0.0f, 1.0f);

        // Level
        dungeon.Render(projection);

        // monsters
        monstersTileSet.Render(8, 0, glm::vec3(2.0f, -2.0f, 0.0f), projection);
        monstersTileSet.Render(8, 0, glm::vec3(4.0f, -1.0f, 0.0f), projection);
        monstersTileSet.Render(8, 1, glm::vec3(5.0f, -6.0f, 0.0f), projection);

        // player
        roguesTileSet.Render(3, 1, position, projection);
        box.Render(position, projection);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwDestroyWindow(window);
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
