#pragma once

#include "./BaseGameState.hpp"
#include "./Sprite.hpp"
#include <vector>

class Game;
class Player;
class Text;
class Music;
class Asteroid;

class GameGameState : public BaseGameState
{
private:
	Game* game;
	std::shared_ptr<Music> music;

private:
	std::shared_ptr<Sprite> backgroundSprite;
	std::shared_ptr<Player> player;
	std::shared_ptr<Text> liveScore;

	int lives;
	int score;

	std::vector<std::shared_ptr<Asteroid>> asteroids;

public:
	GameGameState(Game* mGame);

	// Inherited via BaseGameState
	void enter() override;
	void handleInput(sf::Event aEvent) override;
	void update(sf::Time elapsed) override;
	void render() override;
	void exit() override;

public:
	std::shared_ptr<Asteroid> SpawnAsteroid(float aSizeMultipler = 3, bool useRandomPosition = true);
	int getLives() const;
	void setLives(const int aLives);

	void setScore(const int score);
};

