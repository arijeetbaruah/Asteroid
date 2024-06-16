#pragma once
#include <SFML/Graphics.hpp>

class Text;
class Game;

class Button
{
private:
	Game* game;

	Text* text;
	sf::RectangleShape buttonShape;

	sf::Sprite normal;
	sf::Sprite clicked;

	bool isHovered;
	bool isClicked;

public:

public:
	Button(Game* game, std::string fontFile, std::string aText);

	void setCharacterSize(unsigned int aSize);
	void setFillColor(sf::Color aColor);
	void setStyle(sf::Text::Style aStyle);

	void setText(std::string aText);

	void setPosition(sf::Vector2f aPosition);
	void setPosition(float x, float y);

	void update(sf::Time& elapsed);
	void render();

	void onHoverEnter();
	void onHoverLeave();
	void onClick();

	bool IsHovered() const;
	bool IsClicked() const;
};

