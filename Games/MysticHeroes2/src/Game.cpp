#include "Game.h"

#include "Levels/Levels.h"
#include "Levels/MainMenu.h"


Game::Game(const char* nodeName): Node(nodeName)
{
    // Game Levels
    _gameLevels.push_back(GameLevel { 1, "1. New Sorpigal" });
    _gameLevels.push_back(GameLevel { 2, "2. Goblin Watch Dungeon" });
    _gameLevels.push_back(GameLevel { 3, "3. Sunken Temple Dungeon" });

    // Main Menu
    const auto mainMenu = new MainMenu();
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


void Game::OnLevelOverHandler(int levelStatus)
{

}

void Game::OnLevelWasChosenHandler(int level)
{

}

void Game::OnExitGameHandler(bool isExit)
{

}
