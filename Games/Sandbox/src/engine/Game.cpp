#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "stb_image.h"
#include "Game.h"

Game::Game(GameOptions options)
{
    _window = nullptr;
    _options = options;
    _currentDirectory = std::filesystem::current_path();
}

int Game::Init()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    _window = glfwCreateWindow(
        _options.ScreenWith,
        _options.ScreenHeight,
        _options.WindowTitle.c_str(),
        nullptr, nullptr);

    if (_window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(_window);

    glfwSetFramebufferSizeCallback(_window, FramebufferSizeCallback);

    if (_options.MouseCallback != nullptr)
    {
        glfwSetCursorPosCallback(_window, _options.MouseCallback);
    }

    if (_options.ScrollCallback != nullptr)
    {
        glfwSetScrollCallback(_window, _options.ScrollCallback);
    }

    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Setup Dear ImGui context
    // ---------------------------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    //ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    const char* glsl_version = "#version 130";
    ImGui_ImplOpenGL3_Init(glsl_version);

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    return 0;
}

void Game::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Game::Render()
{
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(_window))
    {
        
    }
}

int Game::Run()
{
    if (!Init())
    {
        return -1;
    }

    Render();

    return 0;
}

Game::~Game()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}