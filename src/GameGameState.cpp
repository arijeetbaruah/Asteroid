#include "../include/GameGameState.h"
#include "../include/Game.h"
#include "../include/Sprite.h"
#include "../include/Player.h"

GameGameState::GameGameState(Game* mGame) : game(mGame)
{
	backgroundSprite = new Sprite(game, "starBG.jpg");
	player = new Player(game);
}

GameGameState::~GameGameState()
{
	delete backgroundSprite;
	delete player;
}

void GameGameState::enter()
{
	backgroundSprite->setScale(4, 3);
	backgroundSprite->setPosition(game->window.getSize().x / 2, game->window.getSize().y / 2);
	player->setPosition(100, 100);
	player->setScale(1, 1);
}

void GameGameState::update(sf::Time elapsed)
{
	player->update(elapsed);
}

void GameGameState::render()
{
	backgroundSprite->render();
	player->render();
}

void GameGameState::exit()
{
}