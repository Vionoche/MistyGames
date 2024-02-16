#include <iostream>

#include "Engine/InputState.h"
#include "Engine/Node.h"
#include "Levels/Level.h"
#include "Monsters/Monsters.h"
#include "PlayerCharacters/Player.h"


class LevelOverListener : public IObserver<int>
{
public:
    void OnNext(const int dataPointer) override
    {
        _levelStatus = dataPointer;
    }

    int GetLevelStatus() const
    {
        return _levelStatus;
    }

private:
    int _levelStatus = 0;
};

int main()
{
    int globalId = 100;

    Node* game = new Node("Game");

    Level* level = new Level("Level");
    const auto levelOverListener = new LevelOverListener();
    const auto levelOverSubscription = level->LevelOverObservable.Subscribe(levelOverListener);

    level->AddNode(new Player("WarriorPlayer"));
    level->AddNode(new Goblin(++globalId));
    level->AddNode(new Goblin(++globalId));
    level->AddNode(new Goblin(++globalId));
    level->AddNode(new Hobgoblin(++globalId));
    level->AddNode(new Skeleton(++globalId));

    game->AddNode(level);

    game->SendNotification(NotificationType::Draw);

    while (InputState::GetInstance().GetInputCode() != 0)
    {
        game->SendNotification(NotificationType::Process);

        NodeDeletingQueue::GetInstance().DeleteNodes();

        std::cout << std::endl;

        game->SendNotification(NotificationType::Draw);

        if (levelOverListener->GetLevelStatus() != 0)
        {
            break;
        }

        std::cout << std::endl;

        InputState::GetInstance().ClearInputCode();
        InputState::GetInstance().ReadInput();
        InputState::GetInstance().ClearInputMessage();
    }

    delete levelOverSubscription;
    delete levelOverListener;
    delete game;

    std::cout << std::endl;
    std::cout << "The End" << std::endl;
}
