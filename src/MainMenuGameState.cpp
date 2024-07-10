#include "../include/MainMenuGameState.hpp"
#include "../include/Game.hpp"
#include "../include/Text.hpp"
#include "../include/Music.hpp"
#include "../include/Button.hpp"
#include "../include/Sprite.hpp"
#include "spdlog/spdlog.h"

MainMenuGameState::MainMenuGameState(Game* mGame): game(mGame)
{
	mainMenuText = std::make_shared<Text>(game, "PlayfairDisplay.ttf", "Asteroid");
	startBtn = std::make_shared<Button>(game, "PlayfairDisplay.ttf", "Start", std::bind(&MainMenuGameState::onStartBtn, this));
	settingsBtn = std::make_shared<Button>(game, "PlayfairDisplay.ttf", "Settings", std::bind(&MainMenuGameState::onSettingsBtn, this));
	exitBtn = std::make_shared<Button>(game, "PlayfairDisplay.ttf", "Quit", std::bind(&MainMenuGameState::onExitBtn, this));
	backgroundSprite = std::make_shared<Sprite>(game, "starBG.jpg");
	music = std::make_shared<Music>("asteroid-110229.mp3");
}

void MainMenuGameState::enter()
{
	backgroundSprite->setScale(4, 3);
	backgroundSprite->setPosition(game->window.getSize().x / 2, game->window.getSize().y / 2);

	mainMenuText->setCharacterSize(100);
	mainMenuText->setFillColor(sf::Color::Red);
	mainMenuText->setStyle(sf::Text::Bold);
	mainMenuText->setPosition(game->window.getSize().x / 2, 100);

	startBtn->setCharacterSize(100);
	startBtn->setFillColor(sf::Color::Black);
	startBtn->setPosition(game->window.getSize().x / 2, 300);

	settingsBtn->setCharacterSize(100);
	settingsBtn->setFillColor(sf::Color::Black);
	settingsBtn->setPosition(game->window.getSize().x / 2, 500);

	exitBtn->setCharacterSize(100);
	exitBtn->setFillColor(sf::Color::Black);
	exitBtn->setPosition(game->window.getSize().x / 2, 700);

	music->play();
	if (!music->getLoop())
	{
		music->setLoop(true);
	}
	music->setVolume(game->settingsData.getMusicVolumeNormalize());
}

void MainMenuGameState::handleInput(sf::Event aEvent)
{
	startBtn->handleInput(aEvent);
	settingsBtn->handleInput(aEvent);
	exitBtn->handleInput(aEvent);
}

void MainMenuGameState::update(sf::Time elapsed)
{
	startBtn->update(elapsed);
	settingsBtn->update(elapsed);
	exitBtn->update(elapsed);
}

void MainMenuGameState::render()
{
	backgroundSprite->render();
	mainMenuText->render();
	startBtn->render();
	settingsBtn->render();
	exitBtn->render();
}

void MainMenuGameState::exit()
{
	startBtn->reset();
	settingsBtn->reset();
	exitBtn->reset();
}

void MainMenuGameState::onStartBtn()
{
	spdlog::info("Game Start!!");
	music->stop();
	game->StartGame();
}

void MainMenuGameState::onSettingsBtn()
{
	game->gotoSettings();
}

void MainMenuGameState::onExitBtn()
{
	game->window.close();
}
