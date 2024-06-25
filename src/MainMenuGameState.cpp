#include "../include/MainMenuGameState.hpp"
#include "../include/Game.hpp"
#include "../include/Text.hpp"
#include "../include/Music.hpp"
#include "../include/Button.hpp"
#include "../include/Sprite.hpp"
#include "spdlog/spdlog.h"

MainMenuGameState::MainMenuGameState(Game* mGame): game(mGame)
{
	mainMenuText = new Text(game, "PlayfairDisplay.ttf", "Asteroid");
	startBtn = new Button(game, "PlayfairDisplay.ttf", "Start");
	settingsBtn = new Button(game, "PlayfairDisplay.ttf", "Settings");
	exitBtn = new Button(game, "PlayfairDisplay.ttf", "Quit");
	backgroundSprite = new Sprite(game, "starBG.jpg");
	music = new Music("asteroid-110229.mp3");
}

MainMenuGameState::~MainMenuGameState()
{
	delete mainMenuText;
	delete startBtn;
	delete exitBtn;
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
