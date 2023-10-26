#include <iostream>
#include <string>

#include "Engine/Observers.h"
#include "Engine/Node.h"

int main()
{
    const std::string message = "Type monster ID for attack: ";
    std::cout << message << std::endl;

    Node n("name");

    TestObservables();
}
