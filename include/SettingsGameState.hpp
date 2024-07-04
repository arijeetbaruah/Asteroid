#pragma once

#include "./BaseGameState.hpp"
#include <SFML/Graphics.hpp>

class Game;
class Text;

class SettingsGameState : public BaseGameState
{
private:
	Game* game;

private:
	std::shared_ptr<Text> masterVolumn;
	std::shared_ptr<Text> musicVolumn;

	int selectedOptions;

public:
	SettingsGameState(Game* mGame);

	// Inherited via BaseGameState
	void enter() override;
	void handleInput(sf::Event event) override;
	void update(sf::Time elapsed) override;
	void render() override;
	void exit() override;

private:
	void updateUI();
};
