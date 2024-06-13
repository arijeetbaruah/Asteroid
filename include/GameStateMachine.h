#pragma once

#include <SFML/Graphics.hpp>

class MainMenuGameState;
class BaseGameState;

class GameStateMachine
{
private:
	std::shared_ptr<MainMenuGameState> mainMenuState;
	std::shared_ptr<BaseGameState> currentState;

public:
	GameStateMachine();
	void setState(std::shared_ptr<BaseGameState> state);
	void update(sf::Time& time);
	void render(sf::RenderWindow& window);
};
