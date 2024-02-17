#pragma once

#include "../Engine/InputState.h"
#include "../Engine/Node.h"
#include "../Monsters/Monster.h"
#include "../Nodes/ConsolePrinter.h"
#include "../PlayerCharacters/Player.h"


enum PlayerStatus
{
    PlayerDied,
    PlayerWin
};


struct LevelOverResult
{
    int LevelId;
    PlayerStatus PlayerStatus;
};


class Level : public ConsolePrinter
{
public:
    Level(const int levelId, const char* nodeName)
        : ConsolePrinter(nodeName), _levelId(levelId)
    {
    }

    Observable<LevelOverResult> LevelOverObservable;

    void Draw() override
    {
        const auto player = FindNode<Player>(_nodes);
        if (player->GetIsDead())
        {
            std::cout << std::endl;
            std::cout << "YOU DIED" << std::endl;
            std::cout << std::endl;
            LevelOverObservable.Emit({ _levelId, PlayerStatus::PlayerDied });
            return;
        }

        const auto monsters = FindNodes<Monster>(_nodes);
        if (monsters.empty())
        {
            std::cout << std::endl;
            std::cout << "YOU WIN!" << std::endl;
            std::cout << std::endl;
            LevelOverObservable.Emit({ _levelId, PlayerStatus::PlayerWin });
            return;
        }

        InputState::GetInstance().SetInputMessage("Type monster id for attack or type 0 to exit: ");
    }

    int GetLevelId() const
    {
        return _levelId;
    }

protected:
    int _levelId = 0;
    int _globalId = 0;
};
