#include "Game.h"
#include "Levels/MainMenu.h"


Game::Game(const char* nodeName): Node(nodeName)
{
    const auto mainMenu = new MainMenu("Main Menu");
    _levelWasChosenSubscription = mainMenu->LevelWasChosenObservable.Subscribe(
        new Listener(this, &Game::OnLevelWasChosenHandler));
    AddNode(mainMenu);

    // TODO: Handle Level switching and pass the Player
}

void Game::Process()
{
    
}

Game::~Game()
{
    delete _gameOverSubscription;
    delete _levelWasChosenSubscription;
    delete _exitGameSubscription;
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
