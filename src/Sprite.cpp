#include "../include/Sprite.h"
#include "../include/Game.h"

#include "spdlog/spdlog.h"

Sprite::Sprite(Game* aGame, std::string aTextureFile): game(aGame)
{
    if (!texture.loadFromFile("../assets/sprites/" + aTextureFile)) {
        spdlog::error("Error loading background image");
        return;
    }

    sprite.setTexture(texture);

    sf::FloatRect _bounds = sprite.getLocalBounds();
    sprite.setOrigin(_bounds.left + _bounds.width / 2.0f, _bounds.top + _bounds.height / 2.0f);
}

void Sprite::setScale(sf::Vector2f scale)
{
    sprite.setScale(scale);
}

void Sprite::setScale(float x, float y)
{
    sprite.setScale(x, y);
}

void Sprite::setTextureRect(sf::IntRect rect)
{
    sprite.setTextureRect(rect);
}

void Sprite::setPosition(sf::Vector2f aPosition)
{
    sprite.setPosition(aPosition);
}

void Sprite::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

sf::Vector2f Sprite::getPosition() const
{
    return sprite.getPosition();
}

float Sprite::getRotation() const
{
    return sprite.getRotation();
}

void Sprite::move(sf::Vector2f aPosition)
{
    sprite.move(aPosition);
}

void Sprite::move(float x, float y)
{
    sprite.move(x, y);
}

void Sprite::rotation(float angle)
{
    sprite.rotate(angle);
}

sf::FloatRect Sprite::GetBounds() const
{
    return sprite.getGlobalBounds();
}

void Sprite::update(sf::Time& elapsed)
{
}

void Sprite::render()
{
    game->window.draw(sprite);
}
