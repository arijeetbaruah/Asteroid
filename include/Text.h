#pragma once
#include <SFML/Graphics.hpp>

class Game;

class Text
{
private:
	Game* game;

	sf::Font font;
	sf::Text text;

public:
	Text(Game* aGame, std::string fontFile, std::string aText);


	void setCharacterSize(unsigned int aSize);
	void setFillColor(sf::Color aColor);
	void setStyle(sf::Text::Style aStyle);
	sf::FloatRect getLocalBounds() const;

	void setText(std::string aText);

	void setPosition(sf::Vector2f aPosition);
	void setPosition(float x, float y);

	void render();
};

