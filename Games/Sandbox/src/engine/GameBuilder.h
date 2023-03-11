#pragma once

#include "Game.h"

class GameBuilder
{
public:
    GameBuilder();

    void SetScreen(unsigned int width, unsigned int height);

    Game* Build() const;

private:
    GameOptions _gameOptions;
};
