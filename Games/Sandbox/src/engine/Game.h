#pragma once

#include <filesystem>

struct GameOptions
{
    unsigned int ScreenWith;
    unsigned int ScreenHeight;
};

class Game
{
public:
    Game(GameOptions options);

    void Run();

    ~Game();

private:
    GameOptions _options;
    std::filesystem::path _currentDirectory;

    void Init();
};
