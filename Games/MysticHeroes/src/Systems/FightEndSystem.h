#pragma once

#include <vector>

#include "../Components/Monster.h"
#include "../Engine/Component.h"
#include "../Engine/Entity.h"
#include "../Engine/System.h"

constexpr int PlayerDied = 1;
constexpr int PlayerWin = 2;

class FightEndSystem : public ISystem
{
public:
    int Process(std::vector<Entity*>& entities) override
    {
        uint32_t playersCount = 0;
        uint32_t monstersCount = 0;

        for (auto& entity : entities)
        {
            if (FindComponent<Player>(entity->Components))
            {
                playersCount++;
            }

            if (FindComponent<Monster>(entity->Components))
            {
                monstersCount++;
            }
        }

        if (playersCount == 0)
        {
            std::cout << "You died" << std::endl;
            return PlayerDied;
        }

        if (monstersCount == 0)
        {
            std::cout << "You win!" << std::endl;
            return PlayerWin;
        }

        return 0;
    }
};