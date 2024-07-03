#include "../include/Player.hpp"
#include "../include/Sprite.hpp"
#include "../include/Game.hpp"
#include "../include/Bullet.hpp"
#include "../include/BulletPool.hpp"
#include "../include/Asteroid.hpp"
#include "../include/Audio.hpp"
#include "../include/GameGameState.hpp"
#include "../include/Trail.hpp"
#include "spdlog/spdlog.h"

#include <cmath>
#include <memory>

Player::Player(Game* mGame) : BaseEntity(mGame), isMoving(false), isRotating(false), shootCooldownAmount(1), shootCooldown(0), trailCooldown(0)
{
	sprite = std::make_shared<Sprite>(game, "player.png");
	bulletPool = std::make_shared<BulletPool>(game, 10, sf::Color::Red, false);
	sf::Vector2u pos = game->window.getSize();
	setPosition(pos.x / 2.0f, pos.y / 2.0f);

	for (size_t index = 0; index < 50; index++)
	{
		std::shared_ptr<Trail> trail = std::make_shared<Trail>(game);
		trails.push_back(trail);
	}

	laserAudio = std::make_shared<Audio>("laser-gun-81720.mp3");
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

void Player::die()
{
	std::shared_ptr<GameGameState> gameGameState = std::dynamic_pointer_cast<GameGameState>(game->getCurrentGameState());
	gameGameState->setLives(gameGameState->getLives() - 1);

	if (gameGameState->getLives() == 0)
	{
		setActive(false);
		game->GameOver();
		return;
	}

	sf::Vector2u pos = game->window.getSize();
	setPosition(pos.x / 2.0f, pos.y / 2.0f);
}

void Player::render()
{
	if (!isActive())
	{
		return;
	}

	sprite->render();

	for (size_t index = 0; index < trails.size(); index++)
	{
		trails[index]->render();
	}
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

	if (trailCooldown > 0)
	{
		trailCooldown -= elapsed.asSeconds();
	}

	if (isMoving)
	{
		sf::Vector2f movement = getForwardVector();
		movement = sf::Vector2f(movement.x * 200 * elapsed.asSeconds(), - movement.y * 200 * elapsed.asSeconds());
		move(movement);

		wrapPlayer();

		for (size_t index = 0; index < trails.size(); index++)
		{
			if (!trails[index]->getEnable() && trailCooldown <= 0)
			{
				trailCooldown = 0.3f;
				trails[index]->setPosition(getPosition());
				trails[index]->reset();
				break;
			}
		}
	}

	if (isRotating)
	{
		float dir = movementDirection.x > 0 ? 1 : -1;
		rotate(150 * dir * elapsed.asSeconds());
	}

	for (size_t index = 0; index < trails.size(); index++)
	{
		trails[index]->update(elapsed);
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
		std::shared_ptr<Bullet> bullet = bulletPool->getBullet();
		bullet->reset();
		bullet->setActive(true);
		
		float radian = sprite->getRotation() * (3.14159265f / 180.0f);
		sf::Vector2f direction = sf::Vector2f(std::sin(radian), -std::cos(radian));
		sf::Vector2f position = getPosition();
		position += sf::Vector2f(20 * std::sin(radian), -20 * std::cos(radian));
		position -= sf::Vector2f(10 * std::cos(radian), -10 * std::sin(radian));
		bullet->setDirection(direction);
		bullet->setPosition(position);

		laserAudio->play();
	}
}

void Player::onCollision(std::shared_ptr<BaseEntity> entity)
{
	std::shared_ptr<Asteroid> asteroid = std::dynamic_pointer_cast<Asteroid>(entity);
	if (asteroid != nullptr && asteroid->canHit())
	{
		spdlog::info("collision");
		die();
		return;
	}
}
