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

    void SetInputMessage(const char* inputMessage)
    {
        _inputMessage = inputMessage;
    }

    void ClearInputMessage()
    {
        _inputMessage.clear();
    }

    void ReadInput()
    {
        if (!_inputMessage.empty())
        {
            std::cout << _inputMessage;
        }

        std::cin >> _inputCode;
    }

    int GetInputCode() const
    {
        return _inputCode;
    }

    void ClearInputCode()
    {
        _inputCode = -1;
    }

private:
    InputState() = default;
    int _inputCode = -1;
    std::string _inputMessage;
};
