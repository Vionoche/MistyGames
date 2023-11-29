#include "../Engine/World.h"
#include "Level.h"
#include "EntityFactory.h"

Level::Level()
{
    _entities.push_back(CreatePlayer(++_globalId));
    _entities.push_back(CreateGoblin(++_globalId));
    _entities.push_back(CreateGoblin(++_globalId));
    _entities.push_back(CreateGoblin(++_globalId));
    _entities.push_back(CreateHobgoblin(++_globalId));
    _entities.push_back(CreateSkeleton(++_globalId));
}

int Level::Process()
{
    if (_firstRender)
    {
        _printEntitiesSystem.Process(_entities);
        _firstRender = false;
        return 0;
    }

    int processResult = _playerInputSystem.Process(_entities);

    processResult = _monsterAttackSystem.Process(_entities);

    processResult = _damageSystem.Process(_entities);

    processResult = _deadEntitiesSystem.Process(_entities);

    processResult = _fightEndSystem.Process(_entities);

    processResult = _printEntitiesSystem.Process(_entities);

    if (processResult > 0)
    {
        return 1;
    }

    return 0;
}

Level::~Level()
{
    for (const auto& entity : _entities)
    {
        delete entity;
    }
}
