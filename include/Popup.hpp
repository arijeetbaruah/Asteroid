#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Game;
class Text;
class Button;

class Popup
{
private:
	Game* game;
	
	std::function<void()> onApply;
	std::function<void()> onCancel;

private:
	std::shared_ptr<Text> text;
	std::shared_ptr<Button> applyBtn;
	std::shared_ptr<Button> cancelBtn;

	sf::RectangleShape backgound;

	bool isEnable;

public:
	Popup(Game* aGame, std::string fontFile, std::string aText, std::function<void()> onApply, std::function<void()> onCancel);

	void hidePop();
	void showPop();
	bool getEnable() const;

	void handleInput(sf::Event event);
	void update(sf::Time& elapsed);
	void render();

	void onApplyEvent() { onApply(); }
	void onCancelEvent() { onCancel(); }
};

