#pragma once

#include <SFML/Graphics.hpp>

class BaseGameState;
class Game;

class GameStateMachine
{
private:
	std::shared_ptr<BaseGameState> currentState;
	Game* game;

public:
	GameStateMachine(Game* mGame);
	void setState(std::shared_ptr<BaseGameState> state);
	void update(sf::Time& time);
	void render();
};
