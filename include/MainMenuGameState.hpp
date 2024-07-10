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
	std::shared_ptr<Text> mainMenuText;
	std::shared_ptr<Button> startBtn;
	std::shared_ptr<Button> settingsBtn;
	std::shared_ptr<Button> exitBtn;
	std::shared_ptr<Sprite> backgroundSprite;

	std::shared_ptr<Music> music;

public:
	MainMenuGameState(Game* mGame);

	void enter() override;

	void handleInput(sf::Event aEvent) override;
	void update(sf::Time elapsed) override;
	void render() override;

	void exit() override;

public:
	void onStartBtn();
	void onSettingsBtn();
	void onExitBtn();

};

