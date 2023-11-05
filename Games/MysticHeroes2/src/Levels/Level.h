#pragma once
#include "../Engine/Node.h"

class Level : public Node
{
public:
    Level(const char* nodeName)
        : Node(nodeName)
    {
    }
};