#pragma once

#include <filesystem>
#include <GLFW/glfw3.h>

struct GameOptions
{
    int ScreenWith;
    int ScreenHeight;
    std::string WindowTitle;

    GLFWcursorposfun MouseCallback;
    GLFWscrollfun ScrollCallback;
};

class Game
{
public:
    Game(GameOptions options);

    int Run();

    ~Game();

private:
    GameOptions _options;
    std::filesystem::path _currentDirectory;
    GLFWwindow* _window;

    int Init();

    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
};
