#pragma once

#include "./BaseGameState.h"
#include <vector>

class Game;
class Sprite;
class Player;
class Asteroid;

class GameGameState : public BaseGameState
{
private:
	Game* game;

private:
	Sprite* backgroundSprite;
	Player* player;

	std::vector<Asteroid*> asteroids;

public:
	GameGameState(Game* mGame);
	~GameGameState();

	// Inherited via BaseGameState
	void enter() override;
	void update(sf::Time elapsed) override;
	void render() override;
	void exit() override;

public:
	void SpawnAsteroid(float aSizeMultipler = 3);
};

