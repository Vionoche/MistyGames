#pragma once

#include "Components/AttackDamage.h"
#include "Components/CharacterExperience.h"
#include "Components/Health.h"
#include "Components/Monster.h"
#include "Components/Player.h"
#include "Components/RewardExperience.h"
#include "Engine/Entity.h"

Entity* CreatePlayer(const int entityId)
{
    Entity* player = new Entity(entityId, "Player");
    player->Components.push_back(std::make_shared<Player>(entityId));
    player->Components.push_back(std::make_shared<Health>(entityId, 1000, 0.0f, 0.0f));
    player->Components.push_back(std::make_shared<CharacterExperience>(entityId, 0));
    player->Components.push_back(std::make_shared<AttackDamage>(entityId, 20, 0));

    return player;
}

Entity* CreateGoblin(const int entityId)
{
    Entity* monster = new Entity(entityId, "Goblin");
    monster->Components.push_back(std::make_shared<Monster>(entityId));
    monster->Components.push_back(std::make_shared<Health>(entityId, 20, 0.0f, 0.0f));
    monster->Components.push_back(std::make_shared<RewardExperience>(entityId, 20));
    monster->Components.push_back(std::make_shared<AttackDamage>(entityId, 5, 0));

    return monster;
}

Entity* CreateHobgoblin(const int entityId)
{
    Entity* monster = new Entity(entityId, "Hobgoblin");
    monster->Components.push_back(std::make_shared<Monster>(entityId));
    monster->Components.push_back(std::make_shared<Health>(entityId, 30, 0.0f, 0.0f));
    monster->Components.push_back(std::make_shared<RewardExperience>(entityId, 50));
    monster->Components.push_back(std::make_shared<AttackDamage>(entityId, 8, 0));

    return monster;
}

Entity* CreateSkeleton(const int entityId)
{
    Entity* monster = new Entity(entityId, "Skeleton");
    monster->Components.push_back(std::make_shared<Monster>(entityId));
    monster->Components.push_back(std::make_shared<Health>(entityId, 50, 0.5f, 0.5f));
    monster->Components.push_back(std::make_shared<RewardExperience>(entityId, 100));
    monster->Components.push_back(std::make_shared<AttackDamage>(entityId, 10, 0));

    return monster;
}