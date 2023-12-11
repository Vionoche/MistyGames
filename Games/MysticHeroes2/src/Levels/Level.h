#pragma once

#include "../Engine/InputState.h"
#include "../Engine/Node.h"
#include "../Monsters/Monster.h"
#include "../Nodes/ConsolePrinter.h"
#include "../PlayerCharacters/Player.h"

// TODO: to enum
constexpr int PlayerDied = 1;
constexpr int PlayerWin = 2;


class Level : public ConsolePrinter
{
public:
    Level(const char* nodeName)
        : ConsolePrinter(nodeName)
    {
    }

    Observable<int> LevelOverObservable;

    void Draw() override
    {
        const auto player = FindNode<Player>(_nodes);
        if (player->GetIsDead())
        {
            std::cout << std::endl;
            std::cout << "YOU DIED" << std::endl;
            std::cout << std::endl;
            LevelOverObservable.Emit(PlayerDied);
            return;
        }

        const auto monsters = FindNodes<Monster>(_nodes);
        if (monsters.empty())
        {
            std::cout << std::endl;
            std::cout << "YOU WIN!" << std::endl;
            std::cout << std::endl;
            LevelOverObservable.Emit(PlayerWin);
            return;
        }

        InputState::GetInstance().SetInputMessage("Type monster id for attack or type 0 to exit: ");
    }

protected:
    int _globalId = 0;
};
