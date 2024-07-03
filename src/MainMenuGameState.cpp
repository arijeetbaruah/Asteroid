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
	startBtn = std::make_shared<Button>(game, "PlayfairDisplay.ttf", "Start");
	settingsBtn = std::make_shared<Button>(game, "PlayfairDisplay.ttf", "Settings");
	exitBtn = std::make_shared<Button>(game, "PlayfairDisplay.ttf", "Quit");
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

	if (startBtn->IsClicked())
	{
		spdlog::info("Game Start!!");
		music->stop();
		game->StartGame();
		return;
	}

	if (settingsBtn->IsClicked())
	{
		game->gotoSettings();
		return;
	}

	if (exitBtn->IsClicked())
	{
		game->window.close();
		return;
	}
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
