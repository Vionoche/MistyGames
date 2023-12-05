#pragma once

#include "../Engine/InputState.h"
#include "../Nodes/ConsolePrinter.h"

class MainMenu : public ConsolePrinter
{
public:
    MainMenu(const char* nodeName)
        : ConsolePrinter(nodeName)
    {
    }

    void Draw() override
    {


        InputState::GetInstance().SetInputMessage("Type menu number to choose a level or type 0 to exit: ");
    }
};