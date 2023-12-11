#pragma once

#include <vector>

#include "Engine/Node.h"
#include "Engine/Signals.h"
#include "Levels/GameLevel.h"


class Game : public Node
{
public:
    Game(const char* nodeName);

    Observable<int> GameOverObservable;

    void Process() override;

    ~Game() override;

private:
    std::vector<GameLevel> _gameLevels;
    Subscription<int>* _levelWasChosenSubscription = nullptr;
    Subscription<bool>* _exitGameSubscription = nullptr;
    Subscription<int>* _levelOverSubscription = nullptr;

    void OnLevelOverHandler(int levelStatus);

    void OnLevelWasChosenHandler(int level);

    void OnExitGameHandler(bool isExit);
};
