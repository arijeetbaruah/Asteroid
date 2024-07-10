#include "../include/Button.hpp"
#include "../include/Game.hpp"
#include "../include/Text.hpp"
#include "spdlog/spdlog.h"

#if _DEBUG
#define ASSET_SPRITES "../assets/sprites/"
#else
#define ASSET_SPRITES "./assets/sprites/"
#endif

Button::Button(Game* aGame, std::string fontFile, std::string aText, std::function<void()> onClick)
    : game(aGame), text(std::make_shared<Text>(game, fontFile, aText)), isClicked(false), isHovered(false), onClickEvent(onClick)
{
    text->setFillColor(sf::Color::Black);

    std::string fileName = "Default3x.png";
    if (!backgroundTexture.loadFromFile(ASSET_SPRITES + fileName)) {
        spdlog::error("Error loading background image");
    }
    fileName = "Hover3x.png";
    if (!hoverTexture.loadFromFile(ASSET_SPRITES + fileName)) {
        spdlog::error("Error loading background image");
    }
    auto size = game->window.getSize();

    background.setTexture(backgroundTexture);
    background.setScale(size.x / 200, 5);

    sf::FloatRect _bounds = background.getLocalBounds();
    background.setOrigin(_bounds.left + _bounds.width / 2.0f, _bounds.top + _bounds.height / 2.0f);
}

void Button::reset()
{
    isHovered = false;
    isClicked = false;
}

void Button::setCharacterSize(unsigned int aSize)
{
    text->setCharacterSize(aSize);
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
    background.setPosition(aPosition);
}

void Button::setPosition(float x, float y)
{
    text->setPosition(x, y);
    background.setPosition(x, y);

    sf::FloatRect _bounds = background.getLocalBounds();
    background.setOrigin(_bounds.left + _bounds.width / 2.0f, _bounds.top + _bounds.height / 2.0f);
}

void Button::setScale(float x, float y)
{
    background.setScale(x, y);
}

void Button::setScale(sf::Vector2f aSize)
{
    background.setScale(aSize);
}

void Button::handleInput(sf::Event aEvent)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(game->window);
    sf::FloatRect buttonRect = background.getGlobalBounds();

    if (isHovered && aEvent.type == sf::Event::MouseButtonPressed && aEvent.mouseButton.button == sf::Mouse::Left) {
        if (!isClicked) {
            isClicked = true;
            onClick();
        }
    }
}

void Button::update(sf::Time& elapsed)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(game->window);
    sf::FloatRect buttonRect = background.getGlobalBounds();

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

void Button::onHoverEnter()
{
    background.setTexture(hoverTexture);
    spdlog::info("Pointer entered button area.");
}

void Button::onHoverLeave()
{
    background.setTexture(backgroundTexture);
    spdlog::info("Pointer left button area.");
}

void Button::onClick()
{
    spdlog::info("Button clicked!");
    onClickEvent();
}

void Button::render()
{
    game->window.draw(background);
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
