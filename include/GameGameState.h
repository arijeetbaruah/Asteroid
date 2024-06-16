#pragma once

#include "./BaseGameState.h"

class Game;
class Sprite;
class Player;

class GameGameState : public BaseGameState
{
private:
	Game* game;

private:
	Sprite* backgroundSprite;
	Player* player;

public:
	GameGameState(Game* mGame);
	~GameGameState();

	// Inherited via BaseGameState
	void enter() override;
	void update(sf::Time elapsed) override;
	void render() override;
	void exit() override;
};

