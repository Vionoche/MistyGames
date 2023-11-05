#pragma once

#include "../Engine/Node.h"

class CharacterName : public Node
{
public:
    CharacterName(const char* nodeName)
        : Node(nodeName)
    {
    }
};