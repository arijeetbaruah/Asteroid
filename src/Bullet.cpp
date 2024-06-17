#include "../include/Bullet.h"
#include "../include/Game.h"

Bullet::Bullet(Game* aGame, sf::Color aColor, sf::Vector2f aPosition, sf::Vector2f aDirection):
	BaseEntity(aGame),
	circle(sf::CircleShape(10)),
	direction(aDirection)
{
	circle.setFillColor(aColor);
	circle.setPosition(aPosition);
	setActive(false);
}

void Bullet::render()
{
	if (!isActive())
	{
		return;
	}

	game->window.draw(circle);
}

void Bullet::update(sf::Time& elapsed)
{
	if (!isActive())
	{
		return;
	}

	sf::Vector2f movement = sf::Vector2f(direction.x * 200 * elapsed.asSeconds(), direction.y * 200 * elapsed.asSeconds());
	circle.move(movement);
}

void Bullet::onCollision(BaseEntity* entity)
{
}

sf::FloatRect Bullet::getBounds()
{
	return circle.getGlobalBounds();
}
