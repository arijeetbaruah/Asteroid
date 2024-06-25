#include "../include/GameGameState.h"
#include "../include/Game.h"
#include "../include/Sprite.h"
#include "../include/Text.h"
#include "../include/Music.hpp"
#include "../include/Player.h"
#include "../include/Asteroid.h"
#include "../include/EntityManager.h"

GameGameState::GameGameState(Game* mGame) : game(mGame), player(0), lives(3)
{
	backgroundSprite = new Sprite(game, "starBG.jpg");
	liveScore = new Text(game, "PlayfairDisplay.ttf", "Score: " + std::to_string(lives));
	liveScore->setPosition(70, 70);
	liveScore->setFillColor(sf::Color::Red);

	music = new Music("space-ambience-56265.mp3");
}

GameGameState::~GameGameState()
{
	delete backgroundSprite;
	delete player;
	delete liveScore;
}

void GameGameState::enter()
{
	player = new Player(game);
	game->getEntityManager()->addEntity(player);
	liveScore->setText("Score: " + std::to_string(lives));

	SpawnAsteroid();

	backgroundSprite->setScale(4, 3);
	backgroundSprite->setPosition(game->window.getSize().x / 2, game->window.getSize().y / 2);
	player->setPosition(game->window.getSize().x / 2, game->window.getSize().y / 2);
	player->setScale(1, 1);

	music->play();
}

void GameGameState::handleInput(sf::Event aEvent)
{
}

Asteroid* GameGameState::SpawnAsteroid(float aSizeMultipler, bool useRandomPosition)
{
	Asteroid* _asteroid = new Asteroid(game);
	_asteroid->initialize(aSizeMultipler, useRandomPosition);
	asteroids.push_back(_asteroid);
	game->getEntityManager()->addEntity(_asteroid);

	return _asteroid;
}

int GameGameState::getLives() const
{
	return lives;
}

void GameGameState::setLives(const int aLives)
{
	lives = std::max(aLives, 0);
	liveScore->setText("Score: " + std::to_string(lives));
}

void GameGameState::update(sf::Time elapsed)
{
}

void GameGameState::render()
{
	backgroundSprite->render();
	liveScore->render();
}

void GameGameState::exit()
{
	music->stop();
}
