#include <iostream>
#include <vector>

#include "Engine/InputState.h"
#include "Engine/Entity.h"
#include "WorldFactory.h"
#include "Systems/DamageSystem.h"
#include "Systems/DeadEntitiesSystem.h"
#include "Systems/FightEndSystem.h"
#include "Systems/MonsterAttackSystem.h"
#include "Systems/PlayerInputSystem.h"
#include "Systems/PrintEntitiesSystem.h"

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

    PrintEntitiesSystem printEntitiesSystem;
    PlayerInputSystem playerInputSystem;
    MonsterAttackSystem monsterAttackSystem;
    DamageSystem damageSystem;
    DeadEntitiesSystem deadEntitiesSystem;
    FightEndSystem fightEndSystem;

    printEntitiesSystem.Process(entities);

    while (InputState::GetInstance().GetInputCode() != 0)
    {
        InputState::GetInstance().Clear();
        InputState::GetInstance().ReadInput();

        int processResult = playerInputSystem.Process(entities);

        processResult = monsterAttackSystem.Process(entities);

        processResult = damageSystem.Process(entities);

        processResult = deadEntitiesSystem.Process(entities);

        processResult = fightEndSystem.Process(entities);

        processResult = printEntitiesSystem.Process(entities);

        if (processResult > 0)
        {
            break;
        }
    }

    for (const auto& entity : entities)
    {
        delete entity;
    }

    std::cout << std::endl;
    std::cout << "The End" << std::endl;
}
