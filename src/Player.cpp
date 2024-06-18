#include "../include/Player.h"
#include "../include/Sprite.h"
#include "../include/Game.h"
#include "../include/Bullet.h"
#include "../include/BulletPool.h"
#include "../include/Asteroid.h"
#include "spdlog/spdlog.h"

#include <cmath>

Player::Player(Game* mGame) : BaseEntity(mGame), isMoving(false), isRotating(false), shootCooldownAmount(1), shootCooldown(0)
{
	sprite = new Sprite(game, "player.png");
	bulletPool = new BulletPool(game, 10, sf::Color::Red, false);
}

Player::~Player()
{
	delete sprite;
}

sf::Vector2f Player::getForwardVector() const
{
	float angleRad = getRotation() * 3.14159265 / 180.0f;
	sf::Vector2f movement(std::sin(angleRad), std::cos(angleRad));

	return movement;
}

void Player::setPosition(sf::Vector2f position)
{
	sprite->setPosition(position);
}

void Player::setPosition(float x, float y)
{
	sprite->setPosition(x, y);
}

sf::Vector2f Player::getPosition() const
{
	return sprite->getPosition();
}

float Player::getRotation() const
{
	return sprite->getRotation();
}

void Player::move(sf::Vector2f position)
{
	sprite->move(position);
}

void Player::move(float x, float y)
{
	sprite->move(x, y);
}

void Player::rotate(float angle)
{
	sprite->rotation(angle);
}

void Player::setScale(float x, float y)
{
	sprite->setScale(x, y);
}

void Player::setScale(sf::Vector2f scale)
{
	sprite->setScale(scale);
}

void Player::handleInput(sf::Time& elapsed)
{
	movementInput();
	shootInput(elapsed);
}

void Player::render()
{
	if (!isActive())
	{
		return;
	}

	sprite->render();
}

void Player::update(sf::Time& elapsed)
{
	if (!isActive())
	{
		return;
	}

	handleInput(elapsed);
	if (shootCooldown > 0)
	{
		shootCooldown -= elapsed.asSeconds();
	}

	if (isMoving)
	{
		sf::Vector2f movement = getForwardVector();
		movement = sf::Vector2f(movement.x * 200 * elapsed.asSeconds(), - movement.y * 200 * elapsed.asSeconds());
		move(movement);

		wrapPlayer();
	}

	if (isRotating)
	{
		float dir = movementDirection.x > 0 ? 1 : -1;
		rotate(150 * dir * elapsed.asSeconds());
	}
}

sf::FloatRect Player::getBounds()
{
	return sprite->GetBounds();
}

void Player::wrapPlayer()
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

void Player::movementInput()
{
	movementDirection = sf::Vector2f(0, 0);
	isMoving = false;
	isRotating = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movementDirection += sf::Vector2f(-1, 0);
		isRotating = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movementDirection += sf::Vector2f(1, 0);
		isRotating = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		movementDirection += sf::Vector2f(0, -1);
		isMoving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		movementDirection += sf::Vector2f(0, 1);
		isMoving = true;
	}

	float movementDirectionMag = std::sqrt(movementDirection.x * movementDirection.x + movementDirection.y * movementDirection.y);
	movementDirection /= movementDirectionMag;
}

void Player::shootInput(sf::Time& elapsed)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		Shoot(elapsed);
	}
}

void Player::Shoot(sf::Time& elapsed)
{
	if (shootCooldown <= 0)
	{
		shootCooldown = shootCooldownAmount;
		Bullet* bullet = bulletPool->getBullet();
		bullet->reset();
		bullet->setActive(true);
		bullet->setPosition(getPosition());
		
		float radian = sprite->getRotation() * (3.14159265f / 180.0f);
		sf::Vector2f direction = sf::Vector2f(std::sin(radian), -std::cos(radian));
		bullet->setDirection(direction);
	}
}

void Player::onCollision(BaseEntity* entity)
{
	Asteroid* asteroid = dynamic_cast<Asteroid*>(entity);
	if (asteroid != nullptr)
	{
		spdlog::info("collision");
		setActive(false);
		return;
	}
}
