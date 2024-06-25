#pragma once

#include "./BaseGameState.h"
#include <vector>

class Game;
class Sprite;
class Player;
class Text;
class Music;
class Asteroid;

class GameGameState : public BaseGameState
{
private:
	Game* game;
	Music* music;

private:
	Sprite* backgroundSprite;
	Player* player;
	Text* liveScore;

	int lives;
	int score;

	std::vector<Asteroid*> asteroids;

public:
	GameGameState(Game* mGame);
	~GameGameState();

	// Inherited via BaseGameState
	void enter() override;
	void handleInput(sf::Event aEvent) override;
	void update(sf::Time elapsed) override;
	void render() override;
	void exit() override;

public:
	Asteroid* SpawnAsteroid(float aSizeMultipler = 3, bool useRandomPosition = true);
	int getLives() const;
	void setLives(const int aLives);

	void setScore(const int score);
};

