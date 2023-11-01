#include <iostream>
#include <string>

#include "Engine/Node.h"

int main()
{
    Node* mainNode = new Node("Game");
    Node* level01 = new Node("Level01");
    level01->AddNode(new Node("Monster01"));
    mainNode->AddNode(level01);
    Node* level02 = new Node("Level02");
    mainNode->AddNode(level02);

    int inputCode = -1;

    while (inputCode != 0)
    {
        // process nodes
        // render nodes

        // clear input

        std::cout << "Type monster id for attack: ";
        std::cin >> inputCode;

        // read input
    }

    delete mainNode;

    std::cout << std::endl;
    std::cout << "The End" << std::endl;
}
