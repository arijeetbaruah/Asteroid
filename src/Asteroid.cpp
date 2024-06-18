#include "../include/Asteroid.h"
#include "../include/Sprite.h"
#include "../include/Game.h"
#include <random>
#include "../include/Bullet.h"


Asteroid::Asteroid(Game* aGame): BaseEntity(aGame), duration(0), animationIndex(0), isHit(false), direction(0)
{
	for (size_t index = 0; index < 3; index++)
	{
		sprite.push_back(new Sprite(game, "asteroids" + std::to_string(index) + ".png"));
		sprite[index]->setScale(3, 3);
	}
}

void Asteroid::initialize()
{
	duration = 0;
	animationIndex = 0;
	isHit = false;

	sf::Vector2f _position = getRandomPosition(game->window);
	sprite[animationIndex]->setPosition(_position);
	direction = getRandomDirection();
}

void Asteroid::setDestroy()
{
	isHit = true;
}

void Asteroid::setPosition(const sf::Vector2f aPosition)
{
	sprite[animationIndex]->setPosition(aPosition);
}

void Asteroid::setPosition(const float x, const float y)
{
	sprite[animationIndex]->setPosition(x, y);
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
			setActive(false);
			return;
		}

		animationIndex++;
		duration = 0;
	}
	sprite[animationIndex]->setPosition(sprite[0]->getPosition());
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
	}
}

sf::FloatRect Asteroid::getBounds()
{
	return sprite[animationIndex]->GetBounds();
}
