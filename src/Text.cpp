#include "../include/Text.hpp"
#include "../include/Game.hpp"
#include "spdlog/spdlog.h"

#if _DEBUG
#define ASSET_FONTS "../assets/fonts/"
#else
#define ASSET_FONTS "./assets/fonts/"
#endif

Text::Text(Game* aGame, std::string fontFile, std::string aText): game(aGame)
{
	if (!font.loadFromFile(ASSET_FONTS + fontFile))
	{
		spdlog::error("Font Not found");
		return;
	}

	text.setFont(font);
	setText(aText);
	sf::FloatRect _bounds = text.getLocalBounds();
	text.setOrigin(_bounds.left + _bounds.width / 2.0f, _bounds.top + _bounds.height / 2.0f);
}

void Text::setCharacterSize(unsigned int aSize)
{
	text.setCharacterSize(aSize);
	sf::FloatRect _bounds = text.getLocalBounds();
	text.setOrigin(_bounds.left + _bounds.width / 2.0f, _bounds.top + _bounds.height / 2.0f);
}

void Text::setFillColor(sf::Color aColor)
{
	text.setFillColor(aColor);
}

void Text::setStyle(sf::Text::Style aStyle)
{
	text.setStyle(aStyle);
}

sf::FloatRect Text::getLocalBounds() const
{
	return text.getLocalBounds();
}

void Text::setText(std::string aText)
{
	text.setString(aText);
}

void Text::setPosition(sf::Vector2f aPosition)
{
	text.setPosition(aPosition);
}

void Text::setPosition(float x, float y)
{
	text.setPosition(x, y);
}

void Text::render()
{
	game->window.draw(text);
}
