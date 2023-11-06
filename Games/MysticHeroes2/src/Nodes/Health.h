#pragma once

#include <iostream>

#include "../Engine/Node.h"
#include "../Engine/Signals.h"
#include "../Nodes/CharacterName.h"

class Health : public Node
{
public:
    Health(
        const char* nodeName,
        const int healthPoints,
        const float physicalResist,
        const float magicResist)
        : Node(nodeName),
          _healthPoints(healthPoints),
          _physicalResist(physicalResist),
          _magicResist(magicResist)
    {
    }

    Observable<int> HealthOverObservable;

    int GetHealthPoints() const
    {
        return _healthPoints;
    }

    float GetPhysicalResist() const
    {
        return _physicalResist;
    }

    float GetMagicResist() const
    {
        return _magicResist;
    }

    void UpdateHealthPoints(const int healthPoints)
    {
        _healthPoints = healthPoints;
    }

    void TakeDamage(const uint32_t takenPhysicalDamage, const uint32_t takenMagicDamage)
    {
        const float physicalCoefficient = 1.0f - _physicalResist;
        const float magicCoefficient = 1.0f - _magicResist;

        const uint32_t physicalDamage = (uint32_t)(physicalCoefficient * (float)takenPhysicalDamage);
        const uint32_t magicDamage = (uint32_t)(magicCoefficient * (float)takenMagicDamage);
        const uint32_t damage = physicalDamage + magicDamage;

        _healthPoints -= (int)damage;

        if (const auto targetName = FindNode<CharacterName>(_parent->GetNodes()))
        {
            std::cout << targetName->GetName() << " gets " << damage << "!" << std::endl;

            if (_healthPoints <= 0)
            {
                std::cout << targetName->GetName() << " dies!" << std::endl;
                HealthOverObservable.Emit(_healthPoints);
            }
        }
    }

private:
    int _healthPoints;
    float _physicalResist;
    float _magicResist;
};
