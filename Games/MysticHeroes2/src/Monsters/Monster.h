#pragma once

#include <cstdint>

#include "../Engine/Node.h"
#include "../Nodes/Health.h"

class Monster : public Node
{
public:
    Monster(int monsterId,
            const char* monsterTitle,
            int healthPoints,
            float physicalResist,
            float magicResist,
            uint32_t rewardExperiencePoints)
        : Node(std::string(monsterTitle + std::to_string(monsterId)).c_str()),
          _monsterId(monsterId),
          _monsterTitle(monsterTitle),
          _rewardExperiencePoints(rewardExperiencePoints)
    {
        AddNode(new Health("Health", healthPoints, physicalResist, magicResist));
    }

    int GetMonsterId() const
    {
        return _monsterId;
    }

    const char* GetMonsterTitle() const
    {
        return _monsterTitle.c_str();
    }

    void DamageHit(const uint32_t takenPhysicalDamage, const uint32_t takenMagicDamage)
    {
        if (const auto health = (Health*)GetNode("Health"))
        {
            health->ProcessDamage(takenPhysicalDamage, takenMagicDamage);
        }
    }

    void Draw() override
    {
        std::cout << _monsterTitle << " (" << _monsterId << ")";

        if (const auto health = (Health*)GetNode("Health"))
        {
            std::cout << " HP " << health->GetHealthPoints() << std::endl;
        }
    }

protected:
    int _monsterId;
    std::string _monsterTitle;
    uint32_t _rewardExperiencePoints;
};
