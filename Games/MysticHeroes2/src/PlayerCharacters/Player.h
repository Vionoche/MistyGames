#pragma once

#include <cstdint>

#include "../Engine/InputState.h"
#include "../Engine/Node.h"
#include "../Monsters/Monster.h"
#include "../Nodes/Health.h"

class Player : public Node
{
public:
    Player(const char* nodeName)
        : Node(nodeName)
    {
        AddNode(new Health("Health", 1000, 0.0f, 0.0f));
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

        Monster* monster = nullptr;

        const auto levelNodes = _parent->GetNodes();

        for (const auto node : levelNodes)
        {
            const auto monsterNode = (Monster*)node;
            if (monsterNode == nullptr)
            {
                std::cout << "This is a player" << std::endl;
                continue;
            }

            if (monsterNode->GetMonsterId() == inputCode)
            {
                monster = monsterNode;
                break;
            }
        }

        if (monster == nullptr)
        {
            return;
        }

        monster->DamageHit(20, 0);
    }

    void Draw() override
    {
        std::cout << _nodeName;

        auto health = (Health*)GetNode("Health");
        if (health)
        {
            std::cout << " HP " << health->GetHealthPoints();
        }

        std::cout << " Exp " << _characterExperiencePoints << std::endl;
    }

protected:
    uint32_t _characterExperiencePoints = 0;
};
