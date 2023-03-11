#pragma once

#include "Game.h"

class GameBuilder
{
public:
    GameBuilder();

    void SetScreen(int width, int height);
    void SetWindowTitle(const std::string& title);
    void SetMouseCallback(GLFWcursorposfun mouseCallback);
    void SetScrollCallback(GLFWscrollfun scrollCallback);

    Game* Build() const;

private:
    GameOptions _gameOptions;
};
