#pragma once

#include "../Engine/Node.h"
#include "../Nodes/CharacterName.h"

class Health : public Node
{
public:
    Health(const char* nodeName, int healthPoints, float physicalResist, float magicResist)
        : Node(nodeName),
          _healthPoints(healthPoints),
          _physicalResist(physicalResist),
          _magicResist(magicResist)
    {
    }

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
        }
    }

private:
    int _healthPoints;
    float _physicalResist;
    float _magicResist;
};