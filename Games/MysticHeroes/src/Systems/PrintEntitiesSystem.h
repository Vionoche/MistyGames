#pragma once

#include <vector>

#include "../Components/Health.h"
#include "../Components/CharacterExperience.h"
#include "../Engine/Entity.h"
#include "../Engine/System.h"

class PrintEntitiesSystem : ISystem
{
public:
    int Process(std::vector<Entity*>& entities) override
    {
        for (auto& entity : entities)
        {
            std::cout << entity->EntityName << "(" << entity->EntityId << ")";

            const Health* health = FindComponent<Health>(entity->Components);
            if (health)
            {
                std::cout << " HP " << health->HealthPoints;
            }

            const CharacterExperience* experience = FindComponent<CharacterExperience>(entity->Components);
            if (experience)
            {
                std::cout << " Exp " << experience->ExperiencePoints;
            }

            std::cout << std::endl;
        }

        return 0;
    }
};