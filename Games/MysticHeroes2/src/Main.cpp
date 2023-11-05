#include <iostream>

#include "Engine/InputState.h"
#include "Engine/Node.h"
#include "Engine/Processing.h"
#include "Monsters/Monsters.h"
#include "PlayerCharacters/Player.h"

int main()
{
    int globalId = 100;
    Node* mainNode = new Node("Game");
    Node* level01 = new Node("Level");
    level01->AddNode(new Player("WarriorPlayer"));
    level01->AddNode(new Goblin(++globalId));
    level01->AddNode(new Goblin(++globalId));
    level01->AddNode(new Goblin(++globalId));
    level01->AddNode(new Hobgoblin(++globalId));
    level01->AddNode(new Skeleton(++globalId));
    mainNode->AddNode(level01);

    while (InputState.GetInputCode() != 0)
    {
        ProcessNodes<&Node::Process>(mainNode);
        ProcessNodes<&Node::Draw>(mainNode);

        InputState.Clear();
        InputState.ReadInput();
    }

    delete mainNode;

    std::cout << std::endl;
    std::cout << "The End" << std::endl;
}
