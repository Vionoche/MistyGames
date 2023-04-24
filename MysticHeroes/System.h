#pragma once

#include <memory>
#include <vector>

#include "Entity.h"
#include "World.h"

void ProcessPlayerInputSystem(const std::vector<std::shared_ptr<Entity>>& entities, int targetId)
{
    const char* playerName = nullptr;
    uint32_t physicalDamage = 0;
    uint32_t magicDamage = 0;

    for (int index = 0; index < static_cast<int>(entities.size()); index++)
    {
        const Entity& entity = *entities[index];
        const Player* player = FindComponent<Player>(entity.Components);
        if (!player)
        {
            continue;
        }

        const AttackDamage* attackDamage = FindComponent<AttackDamage>(entity.Components);
        if (!attackDamage)
        {
            continue;
        }

        playerName = entity.EntityName.c_str();
        physicalDamage = attackDamage->PhysicalDamage;
        magicDamage = attackDamage->MagicDamage;
    }

    if (physicalDamage == 0 && magicDamage == 0)
    {
        return;
    }

    for (int index = 0; index < static_cast<int>(entities.size()); index++)
    {
        Entity& entity = *entities[index];
        if (entity.EntityId != targetId)
        {
            continue;
        }

        const Monster* monster = FindComponent<Monster>(entity.Components);
        if (!monster)
        {
            continue;
        }

        entity.Components.push_back(std::make_shared<TakenDamage>(targetId, physicalDamage, magicDamage));

        std::cout << playerName << " hits " << physicalDamage << "phys and " << magicDamage << "mag damage to " << entity.EntityName << std::endl;
    }
}

void ProcessMonsterAttackSystem(const std::vector<std::shared_ptr<Entity>>& entities)
{

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
    Entity* playerEntity = nullptr;
    for (int index = 0; index < static_cast<int>(entities.size()); index++)
    {
        Entity& entity = *entities[index];
        const Player* player = FindComponent<Player>(entity.Components);
        if (player)
        {
            playerEntity = &entity;
            break;
        }
    }

    for (auto iterator = entities.begin(); iterator != entities.end();)
    {
        const Entity* entity = (*iterator).get();
        const Health* health = FindComponent<Health>(entity->Components);

        if (health && health->HealthPoints <= 0)
        {
            const RewardExperience* reward = FindComponent<RewardExperience>(entity->Components);
            if (reward && playerEntity)
            {
                CharacterExperience* characterExperience = FindComponent<CharacterExperience>(playerEntity->Components);
                if (characterExperience)
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