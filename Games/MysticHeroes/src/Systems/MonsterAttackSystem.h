#pragma once

#include <vector>

#include "AttackSystemBase.h"
#include "../Components/Monster.h"
#include "../Components/Player.h"
#include "../Engine/Component.h"
#include "../Engine/Entity.h"

class MonsterAttackSystem : public AttackSystemBase
{
public:
    int Process(std::vector<Entity*>& entities) override
    {
        Entity* player = FindEntityByComponent<Player>(entities);
        if (!player)
        {
            return 0;
        }

        for (auto& enemy : entities)
        {
            if (const Monster* monster = FindComponent<Monster>(enemy->Components); !monster)
            {
                continue;
            }

            ProcessEntityAttack(*enemy, *player);
        }

        return 0;
    }
};