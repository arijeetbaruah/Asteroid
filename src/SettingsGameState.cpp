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
	masterVolumnValue = game->settingsData.masterVolume;
	musicVolumnValue = game->settingsData.musicVolume;

	masterVolumn->setFillColor(sf::Color::White);
	masterVolumn->setCharacterSize(50);
	masterVolumn->setStyle(sf::Text::Bold);
	masterVolumn->setPosition(game->window.getSize().x / 2, 100);
	masterVolumn->setText("Master Volume " + std::to_string((int)masterVolumnValue));

	musicVolumn->setFillColor(sf::Color::Red);
	musicVolumn->setCharacterSize(50);
	musicVolumn->setStyle(sf::Text::Bold);
	musicVolumn->setPosition(game->window.getSize().x / 2, 300);
	musicVolumn->setText("Music Volume " + std::to_string((int)musicVolumnValue));

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
		game->settingsData.masterVolume = masterVolumnValue;
		game->settingsData.musicVolume = musicVolumnValue;

		std::string settingsData = std::to_string(masterVolumnValue) + "," + std::to_string((int)musicVolumnValue);
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
			masterVolumnValue -= 1;
			masterVolumnValue = masterVolumnValue < 0 ? 0 : masterVolumnValue;
			masterVolumn->setText("Master Volume " + std::to_string((int)masterVolumnValue));
			break;
		case SliderDirection::RIGHT:
			masterVolumnValue += 1;
			masterVolumnValue = masterVolumnValue > 100 ? 100 : masterVolumnValue;
			masterVolumn->setText("Master Volume " + std::to_string((int)masterVolumnValue));
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
				musicVolumnValue -= 1;
				musicVolumnValue = musicVolumnValue < 0 ? 0 : musicVolumnValue;
				musicVolumn->setText("Music Volume " + std::to_string((int)musicVolumnValue));
				break;
			case SliderDirection::RIGHT:
				musicVolumnValue += 1;
				musicVolumnValue = musicVolumnValue > 100 ? 100 : musicVolumnValue;
				musicVolumn->setText("Music Volume " + std::to_string((int)musicVolumnValue));
				break;
			}
		}
	}

}
