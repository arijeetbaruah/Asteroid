#pragma once
#include <SFML/Graphics.hpp>

class BaseGameState
{
public:
	virtual void enter() = 0;
	virtual void update(sf::Time elapsed) = 0;
	virtual void render(sf::RenderWindow& window) =0;
	virtual void exit() = 0;
};

