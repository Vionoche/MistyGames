#include <iostream>
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"

class Health : public Component
{
public:
    int HealthPoints;
    float PhysicalResist;
    float MagicResist;

    Health(
        int entityId,
        int healthPoints,
        float physicalResist,
        float magicResist)
        : Component(entityId), HealthPoints(healthPoints), PhysicalResist(physicalResist), MagicResist(magicResist)
    {
    }

    void PrintName() const override
    {
        std::cout << "Health Component EntityId = " << EntityId << std::endl;
    }
};

class Player : public Component
{
public:
    Player(int entityId) : Component(entityId)
    {
    }
};

class Monster : public Component
{
public:
    Monster(int entityId) : Component(entityId)
    {
    }
};

class CharacterExperience : public Component
{
public:
    uint32_t ExperiencePoints;

    CharacterExperience(int entityId, uint32_t experiencePoints)
        : Component(entityId), ExperiencePoints(experiencePoints)
    {
    }
};

class RewardExperience : public Component
{
public:
    uint32_t ExperiencePoints;

    RewardExperience(int entityId, uint32_t experiencePoints)
        : Component(entityId), ExperiencePoints(experiencePoints)
    {
    }
};

class AttackDamage : public Component
{
public:
    uint32_t PhysicalDamage;
    uint32_t MagicDamage;

    AttackDamage(int entityId, uint32_t physicalDamage, uint32_t magicDamage)
        : Component(entityId), PhysicalDamage(physicalDamage), MagicDamage(magicDamage)
    {
    }
};

class TakenDamage : public Component
{
public:
    uint32_t PhysicalDamage;
    uint32_t MagicDamage;

    TakenDamage(int entityId, uint32_t physicalDamage, uint32_t magicDamage)
        : Component(entityId), PhysicalDamage(physicalDamage), MagicDamage(magicDamage)
    {
    }
};

Entity* CreatePlayer(const int entityId)
{
    Entity* player = new Entity(entityId, "Player");
    player->Components.push_back(std::make_shared<Player>(entityId));
    player->Components.push_back(std::make_shared<Health>(entityId, 100, 0.0f, 0.0f));
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

template<class TComponent>
TComponent* FindComponent(const std::vector<std::shared_ptr<Component>>& components)
{
    for (int index = 0; index < static_cast<int>(components.size()); index++)
    {
        Component* current = components[index].get();
        if (TComponent* component = dynamic_cast<TComponent*>(current))
        {
            return component;
        }
    }

    return nullptr;
}

template<class TComponent>
void RemoveComponent(std::vector<std::shared_ptr<Component>>& components)
{
    for (auto iterator = components.begin(); iterator != components.end();)
    {
        Component* current = (*iterator).get();
        if (TComponent* component = dynamic_cast<TComponent*>(current))
        {
            iterator = components.erase(iterator);
            return;
        }
        ++iterator;
    }
}

void PrintEntities(const std::vector<std::shared_ptr<Entity>>& entities)
{
    for (int index = 0; index < static_cast<int>(entities.size()); index++)
    {
        const Entity& entity = *entities[index];
        std::cout << entity.EntityName << "(" << entity.EntityId << ")";

        const Health* health = FindComponent<Health>(entity.Components);
        if (health)
        {
            std::cout << " HP " << health->HealthPoints;
        }

        const CharacterExperience* experience = FindComponent<CharacterExperience>(entity.Components);
        if (experience)
        {
            std::cout << " Exp " << experience->ExperiencePoints;
        }

        std::cout << std::endl;
    }
}

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

// TODO: Process multiple damages
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
            continue;
        }

        const float physicalCoefficient = 1.0f - health->PhysicalResist;
        const float magicCoefficient = 1.0f - health->MagicResist;

        const uint32_t physicalDamage = (uint32_t)(physicalCoefficient * (float)takenDamage->PhysicalDamage);
        const uint32_t magicDamage = (uint32_t)(magicCoefficient * (float)takenDamage->MagicDamage);
        const uint32_t damage = physicalDamage + magicDamage;
        health->HealthPoints -= (int)damage;

        RemoveComponent<TakenDamage>(entity.Components);

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

int main()
{
    // Init the game
    int globalId = 100;
    std::vector<std::shared_ptr<Entity>> entities;

    std::shared_ptr<Entity> player(CreatePlayer(++globalId));
    entities.push_back(player);

    std::shared_ptr<Entity> goblin1(CreateGoblin(++globalId));
    entities.push_back(goblin1);
    std::shared_ptr<Entity> goblin2(CreateGoblin(++globalId));
    entities.push_back(goblin2);
    std::shared_ptr<Entity> goblin3(CreateGoblin(++globalId));
    entities.push_back(goblin3);

    std::shared_ptr<Entity> hobgoblin(CreateHobgoblin(++globalId));
    entities.push_back(hobgoblin);

    std::shared_ptr<Entity> skeleton(CreateSkeleton(++globalId));
    entities.push_back(skeleton);

    // Main loop
    std::cout << std::endl;

    PrintEntities(entities);

    int inputCode = -1;

    while (inputCode != 0)
    {
        std::cout << "Type monster id for attack: ";
        std::cin >> inputCode;

        ProcessPlayerInputSystem(entities, inputCode);
        
        ProcessDamageSystem(entities);

        ProcessDeadEntitiesSystem(entities);

        // System 4
        // If there is no monster or the player died, finish the game

        // System 5
        // Monsters attacks the player and do damage

        // Refactor systems and move them into separate classes

        // Introduce levels (or worlds)

        // System 6
        // Introduce character levels

        PrintEntities(entities);
    }

    std::cout << std::endl;

    std::cout << "The End" << std::endl;
}
