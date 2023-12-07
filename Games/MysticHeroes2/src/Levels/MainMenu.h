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
    Observable<bool> ExitGameObservable;

    void Process() override
    {
        const auto inputCode = InputState::GetInstance().GetInputCode();

        if (inputCode == 0)
        {
            ExitGameObservable.Emit(true);
            return;
        }

        if (inputCode >= 1 && inputCode <= 3)
        {
            LevelWasChosenObservable.Emit(inputCode);
        }
    }

    void Draw() override
    {
        std::cout << "1. New Sorpigal" << std::endl;
        std::cout << "2. Goblin Watch Dungeon" << std::endl;
        std::cout << "3. Sunken Temple Dungeon" << std::endl;
        std::cout << std::endl;

        InputState::GetInstance().SetInputMessage("Type menu number to choose a level or type 0 to exit: ");
    }
};