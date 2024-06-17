#include "../include/GameGameState.h"
#include "../include/Game.h"
#include "../include/Sprite.h"
#include "../include/Player.h"
#include "../include/Asteroid.h"
#include "../include/EntityManager.h"

GameGameState::GameGameState(Game* mGame) : game(mGame), player(0)
{
	backgroundSprite = new Sprite(game, "starBG.jpg");
}

GameGameState::~GameGameState()
{
	delete backgroundSprite;
	delete player;
}

void GameGameState::enter()
{
	player = new Player(game);
	game->getEntityManager()->addEntity(player);
	Asteroid* asteroid = new Asteroid(game);
	game->getEntityManager()->addEntity(asteroid);

	backgroundSprite->setScale(4, 3);
	backgroundSprite->setPosition(game->window.getSize().x / 2, game->window.getSize().y / 2);
	player->setPosition(100, 100);
	player->setScale(1, 1);
}

void GameGameState::update(sf::Time elapsed)
{
}

void GameGameState::render()
{
	backgroundSprite->render();
}

void GameGameState::exit()
{
}
