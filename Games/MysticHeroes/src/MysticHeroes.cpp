#include <iostream>

#include "Engine/InputState.h"
#include "Worlds/Level.h"

int main()
{
    Level level;

    while (InputState::GetInstance().GetInputCode() != 0)
    {
        const int processResult = level.Process();

        InputState::GetInstance().Clear();
        InputState::GetInstance().ReadInput();

        if (processResult > 0)
        {
            break;
        }
    }

    std::cout << std::endl;
    std::cout << "The End" << std::endl;
}
