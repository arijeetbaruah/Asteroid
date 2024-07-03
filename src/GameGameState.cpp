#include "../include/GameGameState.hpp"
#include "../include/Game.hpp"
#include "../include/Sprite.hpp"
#include "../include/Text.hpp"
#include "../include/Music.hpp"
#include "../include/Player.hpp"
#include "../include/Asteroid.hpp"
#include "../include/EntityManager.hpp"

GameGameState::GameGameState(Game* mGame) : game(mGame), player(0), lives(3), score(0)
{
	backgroundSprite = std::make_shared<Sprite>(game, "starBG.jpg");
	liveScore = std::make_shared<Text>(game, "PlayfairDisplay.ttf", "Score: " + std::to_string(lives));
	liveScore->setPosition(70, 70);
	liveScore->setFillColor(sf::Color::Red);

	music = std::make_shared<Music>("space-ambience-56265.mp3");
}

void GameGameState::enter()
{
	player = std::make_shared<Player>(game);
	game->getEntityManager()->addEntity(player);
	liveScore->setText("Live: " + std::to_string(lives) + " | Score: " + std::to_string(score));

	SpawnAsteroid();

	backgroundSprite->setScale(4, 3);
	backgroundSprite->setPosition(game->window.getSize().x / 2, game->window.getSize().y / 2);
	player->setPosition(game->window.getSize().x / 2, game->window.getSize().y / 2);
	player->setScale(1, 1);

	music->play();
	if (!music->getLoop())
	{
		music->setLoop(true);
	}
}

void GameGameState::handleInput(sf::Event aEvent)
{
}

std::shared_ptr<Asteroid> GameGameState::SpawnAsteroid(float aSizeMultipler, bool useRandomPosition)
{
	std::shared_ptr<Asteroid> _asteroid = std::make_shared<Asteroid>(game);
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
	liveScore->setText("Live: " + std::to_string(lives) + " | Score: " + std::to_string(score));
}

void GameGameState::setScore(const int aScore)
{
	score += aScore;
	liveScore->setText("Live: " + std::to_string(lives) + " | Score: " + std::to_string(score));
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
