#pragma once

#include <cstdint>

#include "../Engine/InputState.h"
#include "../Engine/Node.h"
#include "../Monsters/Monster.h"
#include "../Nodes/Attack.h"
#include "../Nodes/CharacterName.h"
#include "../Nodes/Health.h"

class Player : public Node
{
public:
    Player(const char* nodeName)
        : Node(nodeName)
    {
        AddNode(new CharacterName(nodeName));
        AddNode(new Health("Health", 1000, 0.0f, 0.0f));
        AddNode(new Attack("Attack", 20, 0));
    }

    uint32_t GetCharacterExperiencePoints() const
    {
        return _characterExperiencePoints;
    }

    void Process() override
    {
        const int inputCode = InputState.GetInputCode();
        if (inputCode <= 0)
        {
            return;
        }

        const auto monsters = FindNodes<Monster>(_parent->GetNodes());
        for (const auto monster : monsters)
        {
            if (monster->GetMonsterId() == inputCode)
            {
                if (const auto attack = FindNode<Attack>(_nodes))
                {
                    attack->MakeDamage(monster);
                    break;
                }
            }
        }
    }

    void Draw() override
    {
        if (const auto characterName = FindNode<CharacterName>(_nodes))
        {
            std::cout << characterName->GetName();
        }
        else
        {
            std::cout << "Undefined";
        }

        if (const auto health = (Health*)GetNode("Health"))
        {
            std::cout << " HP " << health->GetHealthPoints();
        }

        std::cout << " Exp " << _characterExperiencePoints << std::endl;
    }

protected:
    uint32_t _characterExperiencePoints = 0;
};
