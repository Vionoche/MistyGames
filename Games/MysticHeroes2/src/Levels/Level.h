#pragma once

#include "../Engine/Node.h"
#include "../Monsters/Monster.h"


class Level : public Node
{
public:
    Level(const char* nodeName)
        : Node(nodeName)
    {
    }

    void Process() override
    {
        const auto monsters = FindNodes<Monster>(_nodes);
        if (monsters.empty())
        {
            std::cout << "You win!" << std::endl;
        }
    }
};
