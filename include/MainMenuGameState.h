#pragma once
#include "./BaseGameState.h"

class MainMenuGameState : public BaseGameState
{
public:
	void enter() override;

	void update(sf::Time elapsed) override;
	void render(sf::RenderWindow& window) override;

	void exit() override;

};

