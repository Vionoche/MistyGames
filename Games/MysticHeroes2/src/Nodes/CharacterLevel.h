#pragma once

#include "../Engine/Node.h"
#include "../Engine/Signals.h"

class CharacterLevel : public Node
{
public:
    CharacterLevel(const char* nodeName)
        : Node(nodeName)
    {
    }

    Observable<uint32_t> LevelUpObservable;

    uint32_t GetCurrentLevel() const
    {
        return _currentLevel;
    }

    uint32_t GetExperiencePoints() const
    {
        return _experiencePoints;
    }

    void AddExperiencePoints(const uint32_t experiencePoints)
    {
        _experiencePoints += experiencePoints;
    }

    void Update(const uint32_t currentLevel, const uint32_t experiencePoints)
    {
        _currentLevel = currentLevel;
        _experiencePoints = experiencePoints;
    }

    void Process() override
    {
        if (_isMaxLevel)
        {
            return;
        }

        if (_currentLevel >= 5)
        {
            _isMaxLevel = true;
            return;
        }

        const uint32_t nextLevelExperiencePoints = _levelTable[_currentLevel - 1];

        if (_experiencePoints >= nextLevelExperiencePoints)
        {
            _currentLevel += 1;
            LevelUpObservable.Emit(_currentLevel);
        }
    }

protected:
    uint32_t _currentLevel = 1;
    uint32_t _experiencePoints = 0;
    bool _isMaxLevel = false;

    uint32_t _levelTable[4] = {
        100,  // 2 lvl
        200,  // 3 lvl
        350,  // 4 lvl
        500   // 5 lvl
    };
};