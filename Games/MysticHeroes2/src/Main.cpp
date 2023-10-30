#include <iostream>
#include <string>

#include "Engine/Node.h"
#include "Engine/SignalsTest.h"

int main()
{
    const std::string message = "Type monster ID for attack: ";
    std::cout << message << std::endl;

    Node n("name");

    TestSignals();
}
