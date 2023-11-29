#pragma once

#include <vector>

#include "../System.h"
#include "../Entity.h"
#include "../World.h"

class DeadEntitiesSystem : public ISystem
{
public:
    int Process(std::vector<Entity*>& entities) override
    {
        const Entity* player = FindEntityByComponent<Player>(entities);

        for (auto iterator = entities.begin(); iterator != entities.end();)
        {
            const Entity* entity = *iterator;
            const Health* health = FindComponent<Health>(entity->Components);

            if (health && health->HealthPoints <= 0)
            {
                const RewardExperience* reward = FindComponent<RewardExperience>(entity->Components);
                if (reward && player)
                {
                    if (CharacterExperience* characterExperience = FindComponent<CharacterExperience>(player->Components))
                    {
                        characterExperience->ExperiencePoints += reward->ExperiencePoints;
                    }
                }

                std::cout << entity->EntityName << " dies!" << std::endl;

                iterator = entities.erase(iterator);
                delete entity;

                continue;
            }

            ++iterator;
        }

        return 0;
    }
};