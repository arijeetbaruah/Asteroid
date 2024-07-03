#include "../include/Button.hpp"
#include "../include/Game.hpp"
#include "../include/Text.hpp"
#include "spdlog/spdlog.h"

Button::Button(Game* aGame, std::string fontFile, std::string aText): game(aGame), text(std::make_shared<Text>(game, fontFile, aText)), isClicked(false), isHovered(false)
{
	buttonShape.setFillColor(sf::Color::White);
    text->setFillColor(sf::Color::Black);

    sf::FloatRect _bounds = buttonShape.getLocalBounds();
    buttonShape.setOrigin(_bounds.left + _bounds.width / 2.0f, _bounds.top + _bounds.height / 2.0f);
}

void Button::reset()
{
    isHovered = false;
    isClicked = false;
    buttonShape.setFillColor(sf::Color::White);
}

void Button::setCharacterSize(unsigned int aSize)
{
	text->setCharacterSize(aSize);
    sf::FloatRect _bounds = text->getLocalBounds();
    sf::Vector2f _size(_bounds.width + 10, _bounds.height + 5);
    buttonShape.setSize(_size);
}

void Button::setFillColor(sf::Color aColor)
{
	text->setFillColor(aColor);
}

void Button::setStyle(sf::Text::Style aStyle)
{
	text->setStyle(aStyle);
}

void Button::setText(std::string aText)
{
	text->setText(aText);
}

void Button::setPosition(sf::Vector2f aPosition)
{
	text->setPosition(aPosition);
	buttonShape.setPosition(aPosition);
}

void Button::setPosition(float x, float y)
{
	text->setPosition(x, y);
	buttonShape.setPosition(x, y);

    sf::FloatRect _bounds = buttonShape.getLocalBounds();
    buttonShape.setOrigin(_bounds.left + _bounds.width / 2.0f, _bounds.top + _bounds.height / 2.0f);
}

void Button::handleInput(sf::Event aEvent)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(game->window);
    sf::FloatRect buttonRect = buttonShape.getGlobalBounds();

    if (buttonRect.contains(static_cast<sf::Vector2f>(mousePos)) && aEvent.type == sf::Event::MouseButtonPressed && aEvent.mouseButton.button == sf::Mouse::Left) {
        if (!isClicked) {
            isClicked = true;
            onClick();
        }
    }
}

void Button::update(sf::Time& elapsed)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(game->window);
	sf::FloatRect buttonRect = buttonShape.getGlobalBounds();

    if (buttonRect.contains(static_cast<sf::Vector2f>(mousePos))) {
        if (!isHovered) {
            isHovered = true;
            onHoverEnter();
        }
    }
    else {
        if (isHovered) {
            isHovered = false;
            onHoverLeave();
        }
    }
}

void Button::onHoverEnter() {
    buttonShape.setFillColor(sf::Color::Green);
    spdlog::info("Pointer entered button area.");
}

void Button::onHoverLeave() {
    buttonShape.setFillColor(sf::Color::White);
    spdlog::info("Pointer left button area.");
}

void Button::onClick() {
    buttonShape.setFillColor(sf::Color::Blue);
    spdlog::info("Button clicked!");
}

void Button::render()
{
    game->window.draw(buttonShape);
	text->render();
}

bool Button::IsHovered() const
{
    return isHovered;
}

bool Button::IsClicked() const
{
    return isClicked;
}
