#pragma once

#include <vector>

#include "AttackSystemBase.h"
#include "../Components/Monster.h"
#include "../Components/Player.h"
#include "../Engine/InputState.h"
#include "../Engine/Entity.h"
#include "../World.h"

class PlayerInputSystem : public AttackSystemBase
{
public:
    int Process(std::vector<Entity*>& entities) override
    {
        const int targetId = InputState::GetInstance().GetInputCode();

        const Entity* player = FindEntityByComponent<Player>(entities);
        if (!player)
        {
            return 0;
        }

        for (auto& enemy : entities)
        {
            if (enemy->EntityId != targetId)
            {
                continue;
            }

            if (const Monster* monster = FindComponent<Monster>(enemy->Components); !monster)
            {
                continue;
            }

            ProcessEntityAttack(*player, *enemy);
        }

        return 0;
    }
};