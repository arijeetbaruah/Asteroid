#pragma once
#include "./BaseGameState.hpp"
#include <SFML/Graphics.hpp>

class Game;
class Text;
class Button;
class Sprite;
class Music;

class MainMenuGameState : public BaseGameState
{
private:
	Game* game;

private:
	Text* mainMenuText;
	Button* startBtn;
	Button* settingsBtn;
	Button* exitBtn;
	Sprite* backgroundSprite;

	Music* music;

public:
	MainMenuGameState(Game* mGame);
	~MainMenuGameState();

	void enter() override;

	void handleInput(sf::Event aEvent) override;
	void update(sf::Time elapsed) override;
	void render() override;

	void exit() override;

};

