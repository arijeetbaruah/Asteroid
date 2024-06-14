#include "../include/Game.h"
#include "../include/BaseGameState.h"
#include "../include/GameStateMachine.h"
#include "../include/MainMenuGameState.h"
#include "../include/AssetManager.h"

Game::Game():
	assetManager(std::make_shared<AssetManager>()),
	stateMachine(std::make_shared<GameStateMachine>(this)),
	mainMenuState(std::make_shared<MainMenuGameState>(this))
{
	setState(mainMenuState);
}

void Game::setState(std::shared_ptr<BaseGameState> state)
{
	stateMachine->setState(state);
}

void Game::update(sf::Time& elapsed)
{
	stateMachine->update(elapsed);
}

void Game::render(sf::RenderWindow& window)
{
	stateMachine->render(window);
}
