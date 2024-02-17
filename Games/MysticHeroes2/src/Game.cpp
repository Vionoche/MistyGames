#include "Game.h"

#include "Levels/Levels.h"
#include "Levels/MainMenu.h"


Game::Game(const char* nodeName): Node(nodeName)
{
    // Game Levels
    _gameLevels.push_back(GameLevel { 1, "New Sorpigal" });
    _gameLevels.push_back(GameLevel { 2, "Goblin Watch Dungeon" });
    _gameLevels.push_back(GameLevel { 3, "Sunken Temple Dungeon" });

    // Main Menu
    const auto mainMenu = new MainMenu(_gameLevels);
    _levelWasChosenSubscription = mainMenu->LevelWasChosenObservable.Subscribe(
        new Listener(this, &Game::OnLevelWasChosenHandler));
    AddNode(mainMenu);


    // TODO: Handle Level switching and pass the Player
    const auto level = new NewSorpigal();
    _levelOverSubscription = level->LevelOverObservable.Subscribe(
        new Listener(this, &Game::OnLevelOverHandler));
}

void Game::Process()
{
    
}

Game::~Game()
{
    delete _levelWasChosenSubscription;
    delete _exitGameSubscription;
    delete _levelOverSubscription;
}


void Game::OnLevelOverHandler(LevelOverResult levelOverResult)
{
    
}

void Game::OnLevelWasChosenHandler(const int level)
{
    for (const auto& gameLevel : _gameLevels)
    {
        if (gameLevel.LevelId == level)
        {
            
        }
    }
}

void Game::OnExitGameHandler(const bool isExit) const
{
    if (isExit)
    {
        GameOverObservable.Emit(0);
    }
}
