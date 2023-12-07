#pragma once
#include "Engine/Node.h"

class Game : public Node
{
public:
    Game(const char* nodeName)
        : Node(nodeName)
    {
        // TODO: Add Player and add coping\saving Player (through DTO)
        // TODO: Add Main Menu
        // TODO: Handle Level switching and pass the Player
    }
};