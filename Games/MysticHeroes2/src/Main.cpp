#include <iostream>
#include <stack>

#include "Engine/InputState.h"
#include "Engine/Node.h"
#include "Engine/Processing.h"

int main()
{
    Node* mainNode = new Node("Game");
    Node* level01 = new Node("Level01");
    level01->AddNode(new Node("Monster01"));
    level01->AddNode(new Node("Monster02"));
    mainNode->AddNode(level01);
    Node* level02 = new Node("Level02");
    Node* building01 = new Node("Building01");
    building01->AddNode(new Node("Table"));
    building01->AddNode(new Node("Stool01"));
    building01->AddNode(new Node("Stool02"));
    level02->AddNode(building01);
    level02->AddNode(new Node("Building02"));
    mainNode->AddNode(level02);

    InputState inputState;

    while (inputState.GetInputCode() != 0)
    {
        ProcessNodes<&Node::Process>(mainNode);
        ProcessNodes<&Node::Draw>(mainNode);

        inputState.Clear();
        inputState.ReadInput();
    }

    delete mainNode;

    std::cout << std::endl;
    std::cout << "The End" << std::endl;
}
