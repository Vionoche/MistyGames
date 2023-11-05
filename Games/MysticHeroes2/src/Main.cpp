#include <iostream>

#include "Engine/InputState.h"
#include "Engine/Node.h"
#include "Engine/Processing.h"
#include "Levels/Level.h"
#include "Monsters/Monsters.h"
#include "PlayerCharacters/Player.h"

int main()
{
    int globalId = 100;
    Node* mainNode = new Node("Game");
    Level* level01 = new Level("Level");
    level01->AddNode(new Player("WarriorPlayer"));
    level01->AddNode(new Goblin(++globalId));
    level01->AddNode(new Goblin(++globalId));
    level01->AddNode(new Goblin(++globalId));
    level01->AddNode(new Hobgoblin(++globalId));
    level01->AddNode(new Skeleton(++globalId));
    mainNode->AddNode(level01);

    bool firstRun = true;

    while (InputState::GetInstance().GetInputCode() != 0)
    {
        if (firstRun)
        {
            firstRun = false;
        }
        else
        {
            ProcessNodes<&Node::Process>(mainNode);
        }

        NodeDeletingQueue::GetInstance().DeleteNodes();

        std::cout << std::endl;
        ProcessNodes<&Node::Draw>(mainNode);

        std::cout << std::endl;
        InputState::GetInstance().Clear();
        InputState::GetInstance().ReadInput();
    }

    delete mainNode;

    std::cout << std::endl;
    std::cout << "The End" << std::endl;
}
