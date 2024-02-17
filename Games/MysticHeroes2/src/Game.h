#pragma once

#include <vector>

#include "Levels/Level.h"
#include "Levels/GameLevel.h"
#include "Engine/Signals.h"
#include "Engine/Node.h"


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
    Subscription<LevelOverResult>* _levelOverSubscription = nullptr;
    Subscription<bool>* _exitGameSubscription = nullptr;

    void OnLevelWasChosenHandler(int level);

    void OnLevelOverHandler(LevelOverResult levelOverResult);

    void OnExitGameHandler(bool isExit) const;
};
