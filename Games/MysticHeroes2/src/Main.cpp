#include <iostream>

#include "Engine/InputState.h"
#include "Engine/Node.h"
#include "Levels/Level.h"
#include "Monsters/Monsters.h"
#include "PlayerCharacters/Player.h"


int GlobalLevelStatus = 0;

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

    Node* game = new Node("Game");

    Level* level = new Level("Level");
    const auto levelOverSubscription = level->LevelOverObservable.Subscribe(new LevelOverListener());

    level->AddNode(new Player("WarriorPlayer"));
    level->AddNode(new Goblin(++globalId));
    level->AddNode(new Goblin(++globalId));
    level->AddNode(new Goblin(++globalId));
    level->AddNode(new Hobgoblin(++globalId));
    level->AddNode(new Skeleton(++globalId));

    game->AddNode(level);

    bool firstRun = true;

    while (InputState::GetInstance().GetInputCode() != 0)
    {
        if (firstRun)
        {
            firstRun = false;
        }
        else
        {
            game->SendNotification(NotificationType::Process);
        }

        NodeDeletingQueue::GetInstance().DeleteNodes();

        std::cout << std::endl;
        game->SendNotification(NotificationType::Draw);

        if (GlobalLevelStatus != 0)
        {
            break;
        }

        std::cout << std::endl;
        InputState::GetInstance().Clear();
        InputState::GetInstance().ReadInput();
    }

    delete levelOverSubscription;
    delete game;

    std::cout << std::endl;
    std::cout << "The End" << std::endl;
}
