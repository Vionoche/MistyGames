#pragma once

#include "../Engine/Node.h"
#include "../Monsters/Monster.h"
#include "../PlayerCharacters/Player.h"


constexpr int PlayerDied = 1;
constexpr int PlayerWin = 2;


class Level : public Node
{
public:
    Level(const char* nodeName)
        : Node(nodeName)
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
        }

        const auto monsters = FindNodes<Monster>(_nodes);
        if (monsters.empty())
        {
            std::cout << std::endl;
            std::cout << "YOU WIN!" << std::endl;
            std::cout << std::endl;
            LevelOverObservable.Emit(PlayerWin);
        }
    }
};
