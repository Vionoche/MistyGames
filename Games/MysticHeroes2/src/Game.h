#pragma once
#include "Engine/Node.h"
#include "Engine/Signals.h"

class Game : public Node
{
public:
    Game(const char* nodeName);

    Observable<int> GameOverObservable;

    void Process() override;

    ~Game() override;

private:
    Subscription<int>* _gameOverSubscription = nullptr;
    Subscription<int>* _levelWasChosenSubscription = nullptr;
    Subscription<bool>* _exitGameSubscription = nullptr;

    void OnLevelOverHandler(int levelStatus);

    void OnLevelWasChosenHandler(int level);

    void OnExitGameHandler(bool isExit);
};
