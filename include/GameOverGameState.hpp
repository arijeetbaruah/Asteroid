#pragma once

#include "./BaseGameState.hpp"

class Game;
class Text;
class Button;

class GameOverGameState : public BaseGameState
{
private:
	Game* game;

private:
	Text* gameOverTxt;
	Button* gameOverBtn;

public:
	GameOverGameState(Game* aGame);

	// Inherited via BaseGameState
	void enter() override;
	void handleInput(sf::Event aEvent);
	void update(sf::Time elapsed) override;
	void render() override;
	void exit() override;
};
