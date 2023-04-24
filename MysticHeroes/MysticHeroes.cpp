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

        // System 7
        // Introduce turn-based system

        // Introduce TextLogging system

        PrintEntities(entities);
    }

    std::cout << std::endl;

    std::cout << "The End" << std::endl;
}
