#include "../include/GameOverGameState.hpp"
#include "../include/Game.hpp"
#include "../include/Text.hpp"
#include "../include/Button.hpp"

GameOverGameState::GameOverGameState(Game* aGame): game(aGame)
{
	gameOverTxt = std::make_shared<Text>(game, "PlayfairDisplay.ttf", "Game Over!!");
	gameOverTxt->setFillColor(sf::Color::Red);

	gameOverBtn = std::make_shared<Button>(game, "PlayfairDisplay.ttf", "return");
}

void GameOverGameState::enter()
{
	gameOverTxt->setPosition(game->window.getSize().x / 2, game->window.getSize().y / 2);

	gameOverBtn->setCharacterSize(100);
	gameOverBtn->setFillColor(sf::Color::Black);
	gameOverBtn->setPosition(game->window.getSize().x / 2 - 30, game->window.getSize().y / 2 + 90);
}

void GameOverGameState::handleInput(sf::Event aEvent)
{
	gameOverBtn->handleInput(aEvent);
}

void GameOverGameState::update(sf::Time elapsed)
{
	gameOverBtn->update(elapsed);

	if (gameOverBtn->IsClicked())
	{
		game->gotoMainMenu();
	}
}

void GameOverGameState::render()
{
	gameOverTxt->render();
	gameOverBtn->render();
}

void GameOverGameState::exit()
{
	gameOverBtn->reset();
}
