#pragma once
#include <SFML/Graphics.hpp>

class BaseGameState
{
public:
	virtual void enter() = 0;
	virtual void handleInput(sf::Event event) = 0;
	virtual void update(sf::Time elapsed) = 0;
	virtual void render() =0;
	virtual void exit() = 0;
};

