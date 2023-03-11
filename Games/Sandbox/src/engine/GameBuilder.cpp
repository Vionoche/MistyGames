#include "GameBuilder.h"

GameBuilder::GameBuilder(): _gameOptions()
{
}

void GameBuilder::SetScreen(unsigned width, unsigned height)
{
    _gameOptions.ScreenWith = width;
    _gameOptions.ScreenHeight = height;
}

Game* GameBuilder::Build() const
{
    return new Game(_gameOptions);
}
