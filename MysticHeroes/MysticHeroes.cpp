#include <iostream>
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"

class Health : public Component
{
public:
    uint32_t HealthPoints;
    uint32_t PhysicalResist;
    uint32_t MagicResist;

    Health(
        int entityId,
        uint32_t healthPoints,
        uint32_t physicalResist,
        uint32_t magicResist)
        : Component(entityId), HealthPoints(healthPoints), PhysicalResist(physicalResist), MagicResist(magicResist)
    {
    }

    void PrintName() const override
    {
        std::cout << "Health Component EntityId = " << EntityId << std::endl;
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

Entity* CreatePlayer(const int entityId)
{
    Entity* player = new Entity(entityId, "Player");
    player->Components.push_back(std::make_shared<Health>(entityId, 100, 0, 0));
    player->Components.push_back(std::make_shared<CharacterExperience>(entityId, 0));
    player->Components.push_back(std::make_shared<AttackDamage>(entityId, 20, 0));

    return player;
}

Entity* CreateGoblin(const int entityId)
{
    Entity* monster = new Entity(entityId, "Goblin");
    monster->Components.push_back(std::make_shared<Health>(entityId, 20, 0, 0));
    monster->Components.push_back(std::make_shared<RewardExperience>(entityId, 20));
    monster->Components.push_back(std::make_shared<AttackDamage>(entityId, 5, 0));

    return monster;
}

Entity* CreateHobgoblin(const int entityId)
{
    Entity* monster = new Entity(entityId, "Hobgoblin");
    monster->Components.push_back(std::make_shared<Health>(entityId, 30, 0, 0));
    monster->Components.push_back(std::make_shared<RewardExperience>(entityId, 50));
    monster->Components.push_back(std::make_shared<AttackDamage>(entityId, 8, 0));

    return monster;
}

Entity* CreateSkeleton(const int entityId)
{
    Entity* monster = new Entity(entityId, "Skeleton");
    monster->Components.push_back(std::make_shared<Health>(entityId, 50, 50, 50));
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

void PrintEntities(const std::vector<std::shared_ptr<Entity>>& entities)
{
    for (int index = 0; index < static_cast<int>(entities.size()); index++)
    {
        const Entity& entity = *entities[index];
        std::cout << entity.EntityName << "(" << entity.EntityId << ")";

        Health* health = FindComponent<Health>(entity.Components);
        if (health)
        {
            std::cout << " HP " << health->HealthPoints;
        }

        std::cout << std::endl;
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

    int inputCode = -1;

    while (inputCode != 0)
    {
        std::cout << "Type monster id for attack: ";
        std::cin >> inputCode;

        // System 1
        // Find players attack damage
        // Calculate output damage and create the Damage Component for chosen monster

        // System 2
        // If Damage Component exists, do the damage (recalculate HP) and remove the Damage Component
        // Log into console

        // System 3
        // If entity with negative HP exists, remove the entity
        // Log into console

        // System 4
        // If there is no monster or player died, finish the game

        PrintEntities(entities);
    }

    std::cout << std::endl;

    std::cout << "The End" << std::endl;
}
