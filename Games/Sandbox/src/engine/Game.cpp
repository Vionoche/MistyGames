#include <GLFW/glfw3.h>

#include "Game.h"

Game::Game(GameOptions options)
{
    _options = options;
    _currentDirectory = std::filesystem::current_path();
}

void Game::Init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Game::Run()
{
}

Game::~Game()
{
    glfwTerminate();
}