#pragma once

#include "../Engine/Node.h"
#include "../Engine/Signals.h"
#include "../Nodes/Attack.h"
#include "../Nodes/CharacterName.h"
#include "../Nodes/Health.h"

class Player;

class Monster : public Node
{
public:
    Monster(
        int monsterId,
        const char* monsterTitle,
        int healthPoints,
        float physicalResist,
        float magicResist,
        uint32_t physicalDamage,
        uint32_t magicDamage,
        uint32_t rewardExperiencePoints)
    : Node(std::string(monsterTitle + std::to_string(monsterId)).c_str()),
    _monsterId(monsterId),
    _rewardExperiencePoints(rewardExperiencePoints)
    {
        AddNode(new CharacterName(monsterTitle));
        AddNode(new Health("Health", healthPoints, physicalResist, magicResist));
        AddNode(new Attack("Attack", physicalDamage, magicDamage));
    }

    Observable<Monster*> MonsterDieEventHandler;

    int GetMonsterId() const
    {
        return _monsterId;
    }

    void Process() override
    {
        const auto attack = FindNode<Attack>(_nodes);
        const auto player = FindNode<Player>(_parent->GetNodes());

        if (attack && player)
        {
            attack->MakeDamage((Node*)player);
        }
    }

    void Draw() override
    {
        const auto characterName = FindNode<CharacterName>(_nodes);
        if (characterName == nullptr)
        {
            std::cout << _nodeName << " doesn't have any name" << std::endl;
            return;
        }

        std::cout << characterName->GetName() << " (" << _monsterId << ")";

        if (const auto health = (Health*)GetNode("Health"))
        {
            std::cout << " HP " << health->GetHealthPoints() << std::endl;
        }
    }

protected:
    int _monsterId;
    uint32_t _rewardExperiencePoints;
};
