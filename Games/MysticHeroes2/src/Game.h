#pragma once
#include "Engine/Node.h"

class Game : public Node
{
public:
    Game(const char* nodeName)
        : Node(nodeName)
    {
    }
};