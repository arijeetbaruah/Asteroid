#include "../include/SettingsGameState.hpp"
#include "../include/Text.hpp"
#include "../include/Game.hpp"

SettingsGameState::SettingsGameState(Game* mGame) : game(mGame)
{
	masterVolumn = std::make_shared<Text>(game, "PlayfairDisplay.ttf", "Master Volume");
	musicVolumn = std::make_shared<Text>(game, "PlayfairDisplay.ttf", "Music Volume");
}

void SettingsGameState::enter()
{
	selectedOptions = 0;

	masterVolumn->setFillColor(sf::Color::White);
	masterVolumn->setCharacterSize(50);
	masterVolumn->setStyle(sf::Text::Bold);
	masterVolumn->setPosition(game->window.getSize().x / 2, 100);

	musicVolumn->setFillColor(sf::Color::Red);
	musicVolumn->setCharacterSize(50);
	musicVolumn->setStyle(sf::Text::Bold);
	musicVolumn->setPosition(game->window.getSize().x / 2, 300);
}

void SettingsGameState::handleInput(sf::Event event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		selectedOptions--;
		if (selectedOptions < 0)
		{
			selectedOptions = 0;
		}
		updateUI();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		selectedOptions++;
		if (selectedOptions > 1)
		{
			selectedOptions = 1;
		}
		updateUI();
	}
}

void SettingsGameState::update(sf::Time elapsed)
{
}

void SettingsGameState::render()
{
	masterVolumn->render();
	musicVolumn->render();
}

void SettingsGameState::exit()
{
}

void SettingsGameState::updateUI()
{
	switch (selectedOptions)
	{
	case 0:
		masterVolumn->setFillColor(sf::Color::White);
		musicVolumn->setFillColor(sf::Color::Red);
		break;
	case 1:
		masterVolumn->setFillColor(sf::Color::Red);
		musicVolumn->setFillColor(sf::Color::White);
		break;
	}
}
