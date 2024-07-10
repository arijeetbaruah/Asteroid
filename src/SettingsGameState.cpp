#include "../include/SettingsGameState.hpp"
#include "../include/SettingsData.hpp"
#include "../include/Text.hpp"
#include "../include/Button.hpp"
#include "../include/Popup.hpp"
#include "../include/FileReadWrite.hpp"
#include "../include/Game.hpp"

SettingsGameState::SettingsGameState(Game* mGame) : game(mGame), hasChanges(false)
{
	masterVolumn = std::make_shared<Text>(game, "PlayfairDisplay.ttf", "Master Volume");
	musicVolumn = std::make_shared<Text>(game, "PlayfairDisplay.ttf", "Music Volume");
	applyBtn = std::make_shared<Button>(game, "PlayfairDisplay.ttf", "Apply", std::bind(&SettingsGameState::onApplyClick, this));
	backBtn = std::make_shared<Button>(game, "PlayfairDisplay.ttf", "Back", std::bind(&SettingsGameState::onBackClick, this));
	popup = std::make_shared<Popup>(game, "PlayfairDisplay.ttf", "You have unsaved changes! Are you sure?", std::bind(&SettingsGameState::OnPopupApply, this), std::bind(&SettingsGameState::OnPopupCancel, this));
}

void SettingsGameState::enter()
{
	selectedOptions = 0;

	settings = game->settingsData;

	sliderDirection = SliderDirection::NONE;
	sf::Vector2u size = game->window.getSize();

	masterVolumn->setFillColor(sf::Color::White);
	masterVolumn->setCharacterSize(50);
	masterVolumn->setStyle(sf::Text::Bold);
	masterVolumn->setPosition(size.x / 2, 100);
	masterVolumn->setText("Master Volume " + std::to_string((int)game->settingsData.masterVolume));

	musicVolumn->setFillColor(sf::Color::Red);
	musicVolumn->setCharacterSize(50);
	musicVolumn->setStyle(sf::Text::Bold);
	musicVolumn->setPosition(size.x / 2, 300);
	musicVolumn->setText("Music Volume " + std::to_string((int)game->settingsData.musicVolume));

	applyBtn->setCharacterSize(50);
	applyBtn->setStyle(sf::Text::Bold);
	applyBtn->setScale(size.x / 300, 5);
	applyBtn->setPosition((size.x / 2) + 200, 900);

	backBtn->setCharacterSize(50);
	backBtn->setStyle(sf::Text::Bold);
	backBtn->setScale(size.x / 300, 5);
	backBtn->setPosition((size.x / 2) - 200, 900);

	popup->hidePop();
}

void SettingsGameState::handleInput(sf::Event event)
{
	applyBtn->handleInput(event);
	backBtn->handleInput(event);
	popup->handleInput(event);

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
	backBtn->update(elapsed);

	popup->update(elapsed);
}

void SettingsGameState::render()
{
	masterVolumn->render();
	musicVolumn->render();
	applyBtn->render();
	backBtn->render();

	popup->render();
}

void SettingsGameState::exit()
{
}

void SettingsGameState::OnPopupApply()
{
	game->gotoMainMenu();
}

void SettingsGameState::OnPopupCancel()
{
	popup->hidePop();
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

	hasChanges = true;

}

void SettingsGameState::onApplyClick()
{
	game->settingsData = settings;

	game->getFileReadWrite()->createFile(settingsSaveFilePath + settingsSaveFile, settings.toYAML());
}

void SettingsGameState::onBackClick()
{
	if (hasChanges)
	{
		popup->showPop();
		applyBtn->reset();
		backBtn->reset();
	}
	else
	{
		game->gotoMainMenu();
	}
}
