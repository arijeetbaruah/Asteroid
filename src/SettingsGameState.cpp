#include "../include/SettingsGameState.hpp"
#include "../include/SettingsData.hpp"
#include "../include/Text.hpp"
#include "../include/Button.hpp"
#include "../include/FileReadWrite.hpp"
#include "../include/Game.hpp"

SettingsGameState::SettingsGameState(Game* mGame) : game(mGame)
{
	masterVolumn = std::make_shared<Text>(game, "PlayfairDisplay.ttf", "Master Volume");
	musicVolumn = std::make_shared<Text>(game, "PlayfairDisplay.ttf", "Music Volume");
	applyBtn = std::make_shared<Button>(game, "PlayfairDisplay.ttf", "Apply");
}

void SettingsGameState::enter()
{
	selectedOptions = 0;
	sliderDirection = SliderDirection::NONE;
	settings.masterVolume = game->settingsData.masterVolume;
	settings.masterVolume = game->settingsData.musicVolume;

	masterVolumn->setFillColor(sf::Color::White);
	masterVolumn->setCharacterSize(50);
	masterVolumn->setStyle(sf::Text::Bold);
	masterVolumn->setPosition(game->window.getSize().x / 2, 100);
	masterVolumn->setText("Master Volume " + std::to_string((int)settings.masterVolume));

	musicVolumn->setFillColor(sf::Color::Red);
	musicVolumn->setCharacterSize(50);
	musicVolumn->setStyle(sf::Text::Bold);
	musicVolumn->setPosition(game->window.getSize().x / 2, 300);
	musicVolumn->setText("Music Volume " + std::to_string((int)settings.masterVolume));

	applyBtn->setCharacterSize(50);
	applyBtn->setStyle(sf::Text::Bold);
	applyBtn->setPosition((game->window.getSize().x / 2) + 100, 900);
}

void SettingsGameState::handleInput(sf::Event event)
{
	applyBtn->handleInput(event);

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		sliderDirection = SliderDirection::LEFT;
		updateVolume();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		sliderDirection = SliderDirection::RIGHT;
		updateVolume();
	}
	else
	{
		sliderDirection = SliderDirection::NONE;
	}
}

void SettingsGameState::update(sf::Time elapsed)
{
	applyBtn->update(elapsed);

	if (applyBtn->IsClicked())
	{
		game->settingsData = settings;

		std::string settingsData = std::to_string(settings.masterVolume) + "," + std::to_string((int)settings.musicVolume);
		game->getFileReadWrite()->createFile(settingsSaveFile, settingsData);
	}
}

void SettingsGameState::render()
{
	masterVolumn->render();
	musicVolumn->render();
	applyBtn->render();
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

void SettingsGameState::updateVolume()
{
	if (selectedOptions == 0)
	{
		switch (sliderDirection)
		{
		case SliderDirection::LEFT:
			settings.masterVolume -= 1;
			settings.masterVolume = settings.masterVolume < 0 ? 0 : settings.masterVolume;
			masterVolumn->setText("Master Volume " + std::to_string((int)settings.masterVolume));
			break;
		case SliderDirection::RIGHT:
			settings.masterVolume += 1;
			settings.masterVolume = settings.masterVolume > 100 ? 100 : settings.masterVolume;
			masterVolumn->setText("Master Volume " + std::to_string((int)settings.masterVolume));
			break;
		}
	}
	else
	{
		if (selectedOptions == 1)
		{
			switch (sliderDirection)
			{
			case SliderDirection::LEFT:
				settings.musicVolume -= 1;
				settings.musicVolume = settings.musicVolume < 0 ? 0 : settings.musicVolume;
				musicVolumn->setText("Music Volume " + std::to_string((int)settings.musicVolume));
				break;
			case SliderDirection::RIGHT:
				settings.musicVolume += 1;
				settings.musicVolume = settings.musicVolume > 100 ? 100 : settings.musicVolume;
				musicVolumn->setText("Music Volume " + std::to_string((int)settings.musicVolume));
				break;
			}
		}
	}

}
