#pragma once

#include <iostream>

class InputState
{
public:
    InputState()
    {
        _inputCode = -1;
    }

    void ReadInput()
    {
        std::cout << "Type monster id for attack or type 0 for exit: ";
        std::cin >> _inputCode;
    }

    void Clear()
    {
        _inputCode = -1;
    }

    int GetInputCode() const
    {
        return _inputCode;
    }

private:
    int _inputCode;
};

static InputState InputState;