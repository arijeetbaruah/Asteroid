#include "../include/Asteroid.hpp"

#include <random>
#include <memory>

#include "../include/Sprite.hpp"
#include "../include/Game.hpp"
#include "../include/GameGameState.hpp"
#include "../include/Bullet.hpp"
#include "../include/Audio.hpp"

#include "spdlog/spdlog.h"

#if _DEBUG
#define ASSET_SPRITES "../assets/sounds/"
#else
#define ASSET_SPRITES "./assets/sounds/"
#endif


Asteroid::Asteroid(Game* aGame): BaseEntity(aGame), duration(0), animationIndex(0), isHit(false), direction(0), sizeMultipler(0)
{
	for (size_t index = 0; index < 3; index++)
	{
		sprite.push_back(new Sprite(game, "asteroids" + std::to_string(index) + ".png"));
		sprite[index]->setScale(3, 3);
	}

	hitAudio = new Audio("asteroid-hitting-something-152511.mp3");
}

void Asteroid::initialize(float aSizeMultipler, bool useRandomPosition)
{
	duration = 0;
	animationIndex = 0;
	sizeMultipler = aSizeMultipler;
	isHit = false;

	for (size_t index = 0; index < 3; index++)
	{
		sprite[index]->setScale(aSizeMultipler, aSizeMultipler);
	}

	if (useRandomPosition)
	{
		sf::Vector2f _position = getRandomPosition(game->window);
		sprite[animationIndex]->setPosition(_position);
	}

	direction = getRandomDirection();
}

void Asteroid::setDestroy()
{
	isHit = true;
}

bool Asteroid::canHit() const
{
	return !isHit;
}

int Asteroid::getScore() const
{
	return sizeMultipler;
}

void Asteroid::setPosition(const sf::Vector2f aPosition)
{
	for (size_t index = 0; index < 3; index++)
	{
		sprite[index]->setPosition(aPosition);
	}
}

void Asteroid::setPosition(const float x, const float y)
{
	for (size_t index = 0; index < 3; index++)
	{
		sprite[animationIndex]->setPosition(x, y);
	}
}

sf::Vector2f Asteroid::getPosition() const
{
	return sprite[animationIndex]->getPosition();
}

void Asteroid::update(sf::Time& elapsed)
{
	if (!isActive())
	{
		return;
	}

	Move(elapsed);
	updateDestroy(elapsed);
}

void Asteroid::Move(sf::Time& elapsed)
{
	if (isHit)
	{
		return;
	}

	float radian = direction * (3.14159265f / 180.0f);
	sf::Vector2f directionVector = sf::Vector2f(std::sin(radian) * 10 * elapsed.asSeconds(), -std::cos(radian) * 10 * elapsed.asSeconds());
	sprite[animationIndex]->move(directionVector);
	wrapPlayer();
}

void Asteroid::wrapPlayer()
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

void Asteroid::updateDestroy(sf::Time& elapsed)
{
	if (!isHit)
	{
		return;
	}

	duration += elapsed.asSeconds();

	if (duration >= 2)
	{
		if (animationIndex == 2)
		{
			if (sizeMultipler > 0)
			{
				//initialize(sizeMultipler - 1, false);
				std::shared_ptr<GameGameState> state = std::dynamic_pointer_cast<GameGameState>(game->getCurrentGameState());
				Asteroid* asteroid1 = state->SpawnAsteroid(sizeMultipler - 1, false);
				asteroid1->setPosition(getPosition());
				Asteroid* asteroid2 = state->SpawnAsteroid(sizeMultipler - 1, false);
				asteroid2->setPosition(getPosition());
			}
			setActive(false);
			return;
		}

		animationIndex++;
		duration = 0;
	}
}

sf::Vector2f Asteroid::getRandomPosition(const sf::RenderWindow& window) const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> disX(0, window.getSize().x);
	std::uniform_real_distribution<> disY(0, window.getSize().y);

	sf::Vector2f position(disX(gen), disY(gen));
	return position;
}

float Asteroid::getRandomDirection() const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> disAngle(0, 360);

	return disAngle(gen);
}

void Asteroid::render()
{
	if (!isActive())
	{
		return;
	}

	sprite[animationIndex]->render();
}

void Asteroid::onCollision(BaseEntity* entity)
{
	Bullet* bullet = dynamic_cast<Bullet*>(entity);
	if (bullet != nullptr && bullet->isActive() && !bullet->canHitPlayer())
	{
		isHit = true;
		animationIndex++;
		bullet->setActive(false);

		std::shared_ptr<GameGameState> gameState = std::dynamic_pointer_cast<GameGameState>(game->getCurrentGameState());
		gameState->setScore(getScore());
		hitAudio->play();
	}
}

sf::FloatRect Asteroid::getBounds()
{
	return sprite[animationIndex]->GetBounds();
}
