#include <iostream>
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"
#include "System.h"
#include "World.h"
#include "WorldFactory.h"

void PrintEntities(const std::vector<std::shared_ptr<Entity>>& entities)
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
}

int main()
{
    // Init the game
    int globalId = 100;
    std::vector<std::shared_ptr<Entity>> entities;

    std::shared_ptr<Entity> player(CreatePlayer(++globalId));
    entities.push_back(player);

    // Init the level (world)
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

        ProcessMonsterAttackSystem(entities);

        ProcessDamageSystem(entities);

        ProcessDeadEntitiesSystem(entities);

        const int fightResult = ProcessFightEndSystem(entities);

        PrintEntities(entities);

        if (fightResult > 0)
        {
            break;
        }

        // Bug: Entity must be released from the memory when it dies

        // Refactor systems and move them into separate classes

        // Introduce levels (worlds)

        // System 6
        // Introduce character levels

        // System 7
        // Introduce turn-based system

        // Improve data structures and search algorithms

        // Introduce TextLogging system
    }

    std::cout << std::endl;
    std::cout << "The End" << std::endl;
}
