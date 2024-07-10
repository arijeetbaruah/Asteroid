#pragma once

#include "./BaseGameState.hpp"
#include "./SettingsData.hpp"
#include <SFML/Graphics.hpp>
#include <functional>

class Game;
class Button;
class Text;
class Popup;

enum SliderDirection
{
	NONE,
	LEFT,
	RIGHT
};

class SettingsGameState : public BaseGameState
{
private:
	Game* game;

private:
	std::shared_ptr<Text> masterVolumn;
	std::shared_ptr<Text> musicVolumn;
	std::shared_ptr<Button> applyBtn;
	std::shared_ptr<Button> backBtn;
	std::shared_ptr<Popup> popup;

	int selectedOptions;

	SettingsData settings;
	SliderDirection sliderDirection;

	bool hasChanges;

public:
	SettingsGameState(Game* mGame);

	// Inherited via BaseGameState
	void enter() override;
	void handleInput(sf::Event event) override;
	void update(sf::Time elapsed) override;
	void render() override;
	void exit() override;

public:
	void OnPopupApply();
	void OnPopupCancel();

private:
	void updateUI();
	void updateVolume();

	void onApplyClick();
	void onBackClick();
};
