#include "../include/Asteroid.h"
#include "../include/Sprite.h"

Asteroid::Asteroid(Game* aGame): BaseEntity(aGame), duration(0)
{
	sprite = new Sprite(game, "asteroids.png");
	sprite->setScale(3, 3);
	sf::Vector2f boundSize = sprite->GetBounds().getSize();
	sf::Vector2i size = sf::Vector2i(boundSize.x / 3, boundSize.y);
	sprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), size));
}

void Asteroid::update(sf::Time& elapsed)
{
	duration += elapsed.asSeconds();
	/*int index = (int)duration & 60;
	sf::Vector2f boundSize = sprite->GetBounds().getSize();
	sf::Vector2i size = sf::Vector2i(boundSize.x / 3, boundSize.y);
	sprite->setTextureRect(sf::IntRect(sf::Vector2i(size.x * index, 0), size));*/
}

void Asteroid::render()
{
	sprite->render();
}

void Asteroid::onCollision(BaseEntity* entity)
{
}

sf::FloatRect Asteroid::getBounds()
{
	return sf::FloatRect();
}
