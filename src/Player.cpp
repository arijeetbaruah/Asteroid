#include "../include/Player.h"
#include "../include/Sprite.h"
#include "../include/Game.h"
#include "spdlog/spdlog.h"

#include <cmath>

Player::Player(Game* mGame) : BaseEntity(mGame), isMoving(false), isRotating(false)
{
	sprite = new Sprite(game, "player.png");
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

void Player::handleInput()
{
	movementInput();
	shootInput();
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

	handleInput();

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

void Player::shootInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		Shoot();
	}
}

void Player::Shoot()
{
}

void Player::onCollision(BaseEntity* entity)
{
}
