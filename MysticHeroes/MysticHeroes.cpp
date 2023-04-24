#include <iostream>
#include <vector>

#include "Component.h"
#include "Entity.h"
#include "System.h"
#include "World.h"
#include "WorldFactory.h"

void PrintEntities(const std::vector<Entity*>& entities)
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
    std::vector<Entity*> entities;

    entities.push_back(CreatePlayer(++globalId));

    // Init the level (world)
    entities.push_back(CreateGoblin(++globalId));
    entities.push_back(CreateGoblin(++globalId));
    entities.push_back(CreateGoblin(++globalId));
    entities.push_back(CreateHobgoblin(++globalId));
    entities.push_back(CreateSkeleton(++globalId));

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

        // Refactor systems and move them into separate classes

        // Introduce levels (worlds)

        // System 6
        // Introduce character levels

        // System 7
        // Introduce turn-based system

        // Improve data structures and search algorithms

        // Introduce text logging system
    }

    for (const auto& entity : entities)
    {
        delete entity;
    }

    std::cout << std::endl;
    std::cout << "The End" << std::endl;
}
