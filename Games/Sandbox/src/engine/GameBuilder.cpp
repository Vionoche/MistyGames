#include "GameBuilder.h"

GameBuilder::GameBuilder(): _gameOptions()
{
}

void GameBuilder::SetScreen(const int width, const int height)
{
    _gameOptions.ScreenWith = width;
    _gameOptions.ScreenHeight = height;
}

void GameBuilder::SetWindowTitle(const std::string& title)
{
    _gameOptions.WindowTitle = title;
}

void GameBuilder::SetMouseCallback(const GLFWcursorposfun mouseCallback)
{
    _gameOptions.MouseCallback = mouseCallback;
}

void GameBuilder::SetScrollCallback(const GLFWscrollfun scrollCallback)
{
    _gameOptions.ScrollCallback = scrollCallback;
}

Game* GameBuilder::Build() const
{
    return new Game(_gameOptions);
}
