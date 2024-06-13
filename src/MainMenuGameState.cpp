#include "../include/MainMenuGameState.h"

void MainMenuGameState::enter()
{
}

void MainMenuGameState::update(sf::Time elapsed)
{
}

void MainMenuGameState::render(sf::RenderWindow& window)
{
	sf::CircleShape shape(50.f);
	window.draw(shape);
}

void MainMenuGameState::exit()
{
}
