#include "../include/GameStateMachine.h"
#include "../include/MainMenuGameState.h"
#include "spdlog/spdlog.h"

GameStateMachine::GameStateMachine() : mainMenuState(std::make_shared<MainMenuGameState>())
{
	setState(mainMenuState);
}

void GameStateMachine::setState(std::shared_ptr<BaseGameState> state)
{
	spdlog::info("State change");

	if (currentState != NULL)
	{
		currentState->exit();
	}
	currentState = state;
	currentState->enter();
}

void GameStateMachine::update(sf::Time& time)
{
	currentState->update(time);
}

void GameStateMachine::render(sf::RenderWindow& window)
{
	currentState->render(window);
}
