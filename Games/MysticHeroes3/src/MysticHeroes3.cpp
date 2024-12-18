#include <filesystem>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stb_image.h>

#include "Actors/PlayerFactory.h"

#include "Engine/FrameBox.h"
#include "Engine/ShaderProgram.h"
#include "Engine/Texture.h"
#include "Engine/TileSet.h"

#include "Systems/Level.h"

#include "Levels/Dungeon.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void processInput(GLFWwindow* window);

// Game Settings
bool ShowGrid = false;

// Camera
float windowWidth = 1024.0f;
float windowHeight = 800.0f;
float deltaX = 1.0f;
float deltaY = -0.8f;
float cameraSpeed = 0.5f;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Mouse
bool leftMouseButtonClicked = false;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

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
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetKeyCallback(window, keyCallback);

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

    // Create FrameBox
    FrameBox frameBox;

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

    // Create player
    Player* player = PlayerFactory::CreateMage();

    // Create level
    Level* level = new Dungeon(decorationsTileSet, monstersTileSet, roguesTileSet, frameBox, *player);
    
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

        float ndcMouseX = (static_cast<float>(mouseX) / windowWidth) * 2.0f - 1.0f;
        float ndcMouseY = 1.0f - (static_cast<float>(mouseY) / windowHeight) * 2.0f;

        float worldMouseX = (ndcMouseX + 1.0f) / 2.0f * (orthoRight - orthoLeft) + orthoLeft;
        float worldMouseY = (ndcMouseY + 1.0f) / 2.0f * (orthoTop - orthoBottom) + orthoBottom;

        level->ProcessInput(glm::vec2(worldMouseX, worldMouseY), leftMouseButtonClicked);
        leftMouseButtonClicked = false;

        // Render UI
        // ---------
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Debug Info");
        ImGui::Text("Cursor Position: X: %.3f Y: %.3f", worldMouseX, worldMouseY);
        ImGui::End();

        ImGui::Begin("Game Settings");
        if (ImGui::Button("Toggle Grid"))
        {
            ShowGrid = !ShowGrid;
        }
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
        level->Render(projection, ShowGrid);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete level;
    delete player;

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

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    windowWidth = static_cast<float>(width);
    windowHeight = static_cast<float>(height);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        leftMouseButtonClicked = true;
    }
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    /*if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_W)
        {
            // One step
        }
    }*/
}