#include "../include/Trail.h"
#include "../include/Game.h"

#include <math.h>

Trail::Trail(Game* aGame): game(aGame), timer(5.0f), isEnable(false)
{
	shape = sf::CircleShape(5);
	shape.setFillColor(sf::Color::White);
}

void Trail::reset()
{
	timer = 5.0f;
	isEnable = true;
	shape.setRadius(5);
}

void Trail::setPosition(sf::Vector2f aPosition)
{
	shape.setPosition(aPosition);
}

bool Trail::getEnable() const
{
	return isEnable;
}

void Trail::update(sf::Time& elapsed)
{
	if (timer > 0)
	{
		timer -= elapsed.asSeconds();
		int radius = std::ceil(timer);
		shape.setRadius(radius);
	}
	else
	{
		isEnable = false;
	}
}

void Trail::render()
{
	if (isEnable)
	{
		game->window.draw(shape);
	}
}
