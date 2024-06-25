#include "../include/Bullet.hpp"
#include "../include/Game.hpp"

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

sf::Vector2f Bullet::getPosition() const
{
	return circle.getPosition();
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
	wrapPlayer();
}

void Bullet::wrapPlayer()
{
	sf::Vector2f position = getPosition();
	float spriteWidth = getBounds().width;
	float spriteHeight = getBounds().height;

	if (position.x + spriteWidth < 0) {
		position.x = game->window.getSize().x;
	}
	else if (position.x > game->window.getSize().x) {
		position.x = -spriteWidth;
	}

	if (position.y + spriteHeight < 0) {
		position.y = game->window.getSize().y;
	}
	else if (position.y > game->window.getSize().y) {
		position.y = -spriteHeight;
	}

	setPosition(position);
}

void Bullet::onCollision(BaseEntity* entity)
{
}

sf::FloatRect Bullet::getBounds()
{
	return circle.getGlobalBounds();
}
