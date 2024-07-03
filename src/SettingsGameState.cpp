#include "../include/SettingsGameState.hpp"
#include "../include/Game.hpp"

SettingsGameState::SettingsGameState(Game* mGame) : game(mGame)
{
	returnBtn = std::make_shared<Button>(game, "PlayfairDisplay.ttf", "Return");
}

void SettingsGameState::enter()
{
	returnBtn->setCharacterSize(100);
	returnBtn->setFillColor(sf::Color::Red);
	returnBtn->setStyle(sf::Text::Bold);
	returnBtn->setPosition(game->window.getSize().x / 2, 900);
	returnBtn->reset();
}

void SettingsGameState::handleInput(sf::Event event)
{
	returnBtn->handleInput(event);
}

void SettingsGameState::update(sf::Time elapsed)
{
	returnBtn->update(elapsed);

	if (returnBtn->IsClicked())
	{
		game->gotoMainMenu();
		return;
	}
}

void SettingsGameState::render()
{
	returnBtn->render();
}

void SettingsGameState::exit()
{
}
