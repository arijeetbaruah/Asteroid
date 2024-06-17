#include "../include/Bullet.h"
#include "../include/Game.h"

Bullet::Bullet(Game* aGame, sf::Color aColor, bool aHitPlayer):
	BaseEntity(aGame),
	circle(sf::CircleShape(10)),
	lifeSpan(5),
	hitPlayer(aHitPlayer)
{
	circle.setFillColor(aColor);
	setActive(false);
}

void Bullet::reset()
{
	lifeSpan = 5;
}

void Bullet::setPosition(sf::Vector2f aPosition)
{
	circle.setPosition(aPosition);
}

bool Bullet::canHitPlayer() const
{
	return hitPlayer;
}

void Bullet::setPosition(float x, float y)
{
	circle.setPosition(x, y);
}

void Bullet::setDirection(sf::Vector2f aDirection)
{
	direction = aDirection;
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

	lifeSpan -= elapsed.asSeconds();
	if (lifeSpan <= 0)
	{
		setActive(false);
	}

	sf::Vector2f movement = sf::Vector2f(direction.x * 300 * elapsed.asSeconds(), direction.y * 300 * elapsed.asSeconds());
	circle.move(movement);
}

void Bullet::onCollision(BaseEntity* entity)
{
}

sf::FloatRect Bullet::getBounds()
{
	return circle.getGlobalBounds();
}
