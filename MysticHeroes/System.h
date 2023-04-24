#pragma once

#include <memory>
#include <vector>

#include "Entity.h"
#include "World.h"

void ProcessEntityAttack(const Entity& attacker, Entity& defender)
{
    const AttackDamage* attackDamage = FindComponent<AttackDamage>(attacker.Components);
    if (!attackDamage)
    {
        return;
    }

    if (attackDamage->PhysicalDamage == 0 && attackDamage->MagicDamage == 0)
    {
        return;
    }

    defender.Components.push_back(
        std::make_shared<TakenDamage>(
            defender.EntityId, attackDamage->PhysicalDamage, attackDamage->MagicDamage));

    std::cout << attacker.EntityName
              << " hits " << attackDamage->PhysicalDamage << " physical and "
              << attackDamage->MagicDamage << " magic damage to "
              << defender.EntityName << std::endl;
}

void ProcessPlayerInputSystem(const std::vector<std::shared_ptr<Entity>>& entities, int targetId)
{
    const Entity* player = FindEntityByComponent<Player>(entities);
    if (!player)
    {
        return;
    }

    for (int index = 0; index < static_cast<int>(entities.size()); index++)
    {
        Entity& enemy = *entities[index];
        if (enemy.EntityId != targetId)
        {
            continue;
        }

        if (const Monster* monster = FindComponent<Monster>(enemy.Components); !monster)
        {
            continue;
        }

        ProcessEntityAttack(*player, enemy);
    }
}

void ProcessMonsterAttackSystem(const std::vector<std::shared_ptr<Entity>>& entities)
{
    Entity* player = FindEntityByComponent<Player>(entities);
    if (!player)
    {
        return;
    }

    for (int index = 0; index < static_cast<int>(entities.size()); index++)
    {
        Entity& enemy = *entities[index];

        if (const Monster* monster = FindComponent<Monster>(enemy.Components); !monster)
        {
            continue;
        }

        ProcessEntityAttack(enemy, *player);
    }
}

void ProcessDamageSystem(const std::vector<std::shared_ptr<Entity>>& entities)
{
    for (int index = 0; index < static_cast<int>(entities.size()); index++)
    {
        Entity& entity = *entities[index];
        const TakenDamage* takenDamage = FindComponent<TakenDamage>(entity.Components);
        if (!takenDamage)
        {
            continue;
        }

        Health* health = FindComponent<Health>(entity.Components);
        if (!health)
        {
            RemoveComponentByPointer<TakenDamage>(takenDamage, entity.Components);
            continue;
        }

        const float physicalCoefficient = 1.0f - health->PhysicalResist;
        const float magicCoefficient = 1.0f - health->MagicResist;

        const uint32_t physicalDamage = (uint32_t)(physicalCoefficient * (float)takenDamage->PhysicalDamage);
        const uint32_t magicDamage = (uint32_t)(magicCoefficient * (float)takenDamage->MagicDamage);
        const uint32_t damage = physicalDamage + magicDamage;
        health->HealthPoints -= (int)damage;

        RemoveComponentByPointer<TakenDamage>(takenDamage, entity.Components);

        std::cout << entity.EntityName << " gets " << damage << "!" << std::endl;
    }
}

void ProcessDeadEntitiesSystem(std::vector<std::shared_ptr<Entity>>& entities)
{
    const Entity* player = FindEntityByComponent<Player>(entities);
    if (!player)
    {
        return;
    }

    for (auto iterator = entities.begin(); iterator != entities.end();)
    {
        const Entity* entity = (*iterator).get();
        const Health* health = FindComponent<Health>(entity->Components);

        if (health && health->HealthPoints <= 0)
        {
            if (const RewardExperience* reward = FindComponent<RewardExperience>(entity->Components))
            {
                if (CharacterExperience* characterExperience = FindComponent<CharacterExperience>(player->Components))
                {
                    characterExperience->ExperiencePoints += reward->ExperiencePoints;
                }
            }

            iterator = entities.erase(iterator);

            std::cout << entity->EntityName << " dies!" << std::endl;

            return;
        }

        ++iterator;
    }
}