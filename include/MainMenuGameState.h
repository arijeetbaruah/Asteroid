#pragma once
#include "./BaseGameState.h"
#include <SFML/Graphics.hpp>

class Game;

class MainMenuGameState : public BaseGameState
{
private:
	Game* game;
	sf::Font mainMenuFont;

public:
	MainMenuGameState(Game* mGame);
	void enter() override;

	void update(sf::Time elapsed) override;
	void render(sf::RenderWindow& window) override;

	void exit() override;

};

