#include <iostream>

#include "Engine/InputState.h"
#include "Engine/Node.h"
#include "Engine/Processing.h"
#include "Levels/Level.h"
#include "Monsters/Monsters.h"
#include "PlayerCharacters/Player.h"


int GlobalLevelStatus = 0;

typedef
void (*LevelOverHandler)(int);

class LevelOverListener : public IObserver<int>
{
public:
    void OnNext(const int dataPointer) override
    {
        GlobalLevelStatus = dataPointer;
    }
};

int main()
{
    int globalId = 100;

    Node* mainNode = new Node("Game");

    Level* level = new Level("Level");
    const auto levelOverSubscription = level->LevelOverObservable.Subscribe(new LevelOverListener());

    level->AddNode(new Player("WarriorPlayer"));
    level->AddNode(new Goblin(++globalId));
    level->AddNode(new Goblin(++globalId));
    level->AddNode(new Goblin(++globalId));
    level->AddNode(new Hobgoblin(++globalId));
    level->AddNode(new Skeleton(++globalId));

    mainNode->AddNode(level);

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

        if (GlobalLevelStatus != 0)
        {
            break;
        }

        std::cout << std::endl;
        InputState::GetInstance().Clear();
        InputState::GetInstance().ReadInput();
    }

    delete levelOverSubscription;
    delete mainNode;

    std::cout << std::endl;
    std::cout << "The End" << std::endl;
}
