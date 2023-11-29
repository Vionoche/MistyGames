#pragma once

#include <vector>

#include "../Components/Health.h"
#include "../Components/TakenDamage.h"
#include "../Engine/Component.h"
#include "../Engine/Entity.h"
#include "../Engine/System.h"

class DamageSystem : public ISystem
{
public:
    int Process(std::vector<Entity*>& entities) override
    {
        for (auto& defender : entities)
        {
            Health* health = FindComponent<Health>(defender->Components);
            if (!health)
            {
                RemoveComponentByType<TakenDamage>(defender->Components);
                continue;
            }

            const float physicalCoefficient = 1.0f - health->PhysicalResist;
            const float magicCoefficient = 1.0f - health->MagicResist;

            const std::vector<TakenDamage*> takenDamages = FindComponents<TakenDamage>(defender->Components);

            for (auto& takenDamage : takenDamages)
            {
                const uint32_t physicalDamage = (uint32_t)(physicalCoefficient * (float)takenDamage->PhysicalDamage);
                const uint32_t magicDamage = (uint32_t)(magicCoefficient * (float)takenDamage->MagicDamage);
                const uint32_t damage = physicalDamage + magicDamage;
                health->HealthPoints -= (int)damage;

                RemoveComponentByPointer<TakenDamage>(takenDamage, defender->Components);

                std::cout << defender->EntityName << " gets " << damage << "!" << std::endl;
            }
        }

        return 0;
    }
};