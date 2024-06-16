#pragma once

#include <SFML/Graphics.hpp>
#include "./BaseEntity.h"

class Bullet : public BaseEntity
{
private:
	sf::CircleShape circle;
	sf::Vector2f direction;

public:
	Bullet(Game* aGame, sf::Color aColor, sf::Vector2f aPosition, sf::Vector2f aDirection);

	// Inherited via BaseEntity
	void render() override;
	void update(sf::Time& elapsed) override;
	void onCollision(BaseEntity* entity) override;
	sf::FloatRect getBounds() override;
};

