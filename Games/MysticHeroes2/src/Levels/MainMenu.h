#pragma once

#include <iostream>
#include <utility>
#include <vector>

#include "../Engine/InputState.h"
#include "../Engine/Signals.h"
#include "../Levels/GameLevel.h"
#include "../Nodes/ConsolePrinter.h"

class MainMenu : public ConsolePrinter
{
public:
    MainMenu(std::vector<GameLevel> gameLevels)
        : ConsolePrinter("Main menu")
    {
        _gameLevels = std::move(gameLevels);
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

        for (const auto& gameLevel : _gameLevels)
        {
            if (gameLevel.LevelId == inputCode)
            {
                LevelWasChosenObservable.Emit(inputCode);
                return;
            }
        }
    }

    void Draw() override
    {
        for (const auto& gameLevel : _gameLevels)
        {
            std::cout << gameLevel.LevelId << ". " << gameLevel.LevelName << std::endl;
        }

        std::cout << std::endl;

        InputState::GetInstance().SetInputMessage("Type menu number to choose a level or type 0 to exit: ");
    }

private:
    std::vector<GameLevel> _gameLevels;
};