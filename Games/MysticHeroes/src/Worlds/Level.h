#pragma once

#include <vector>

#include "../Engine/Entity.h"
#include "../Engine/World.h"
#include "../Systems/PrintEntitiesSystem.h"
#include "../Systems/PlayerInputSystem.h"
#include "../Systems/MonsterAttackSystem.h"
#include "../Systems/DamageSystem.h"
#include "../Systems/DeadEntitiesSystem.h"
#include "../Systems/FightEndSystem.h"

class Level : public World
{
public:
    Level();

    int Process() override;

    ~Level() override;

protected:
    int _globalId = 100;
    std::vector<Entity*> _entities;
    PrintEntitiesSystem _printEntitiesSystem;
    PlayerInputSystem _playerInputSystem;
    MonsterAttackSystem _monsterAttackSystem;
    DamageSystem _damageSystem;
    DeadEntitiesSystem _deadEntitiesSystem;
    FightEndSystem _fightEndSystem;

private:
    bool _firstRender = true;
};
