#pragma once

#include <SFML/Graphics.hpp>

class GameStateMachine
{
private:

public:
	void Update(sf::Time& time);
	void Render(sf::RenderWindow& window);
};
