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
        std::make_shared<TakenDamage>(defender.EntityId, attackDamage->PhysicalDamage, attackDamage->MagicDamage));

    std::cout << attacker.EntityName
              << " hits " << attackDamage->PhysicalDamage << " physical and "
              << attackDamage->MagicDamage << " magic damage to "
              << defender.EntityName << std::endl;
}

void ProcessPlayerInputSystem(const std::vector<Entity*>& entities, int targetId)
{
    const Entity* player = FindEntityByComponent<Player>(entities);
    if (!player)
    {
        return;
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
}

void ProcessMonsterAttackSystem(const std::vector<Entity*>& entities)
{
    Entity* player = FindEntityByComponent<Player>(entities);
    if (!player)
    {
        return;
    }

    for (auto& enemy : entities)
    {
        if (const Monster* monster = FindComponent<Monster>(enemy->Components); !monster)
        {
            continue;
        }

        ProcessEntityAttack(*enemy, *player);
    }
}

void ProcessDamageSystem(const std::vector<Entity*>& entities)
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
}

void ProcessDeadEntitiesSystem(std::vector<Entity*>& entities)
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
}

constexpr int PlayerDied = 1;
constexpr int PlayerWin = 2;

int ProcessFightEndSystem(const std::vector<Entity*>& entities)
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