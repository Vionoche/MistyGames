#pragma once

#include <iostream>

#include "../Engine/InputState.h"
#include "../Engine/Signals.h"
#include "../Nodes/ConsolePrinter.h"

class MainMenu : public ConsolePrinter
{
public:
    MainMenu(const char* nodeName)
        : ConsolePrinter(nodeName)
    {
    }

    Observable<int> LevelWasChosenObservable;

    void Process() override
    {
        const auto inputCode = InputState::GetInstance().GetInputCode();

        switch (inputCode)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
        }
    }

    void Draw() override
    {
        std::cout << "1. New Sorpigal" << std::endl;
        std::cout << "2. Goblin Watch Dungeon" << std::endl;
        std::cout << "3. Sunken Temple Dungeon" << std::endl;

        InputState::GetInstance().SetInputMessage("Type menu number to choose a level or type 0 to exit: ");
    }
};