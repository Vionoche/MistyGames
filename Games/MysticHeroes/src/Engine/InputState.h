#pragma once
#include <iostream>

class InputState
{
public:
    InputState(InputState const&) = delete;

    void operator=(InputState const&) = delete;

    static InputState& GetInstance()
    {
        static InputState instance;
        return instance;
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
    InputState() = default;
    int _inputCode = -1;
};
