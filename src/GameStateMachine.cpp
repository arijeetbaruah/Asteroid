#include "../include/GameStateMachine.h"
#include "../include/MainMenuGameState.h"
#include "../include/Game.h"
#include "spdlog/spdlog.h"

GameStateMachine::GameStateMachine(Game* mGame) : game(mGame)
{
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

std::shared_ptr<BaseGameState> GameStateMachine::getCurrentState() const
{
	return currentState;
}

void GameStateMachine::update(sf::Time& time)
{
	currentState->update(time);
}

void GameStateMachine::render()
{
	currentState->render();
}
