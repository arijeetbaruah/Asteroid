#pragma once

#include <SFML/Graphics.hpp>
#include "./BaseEntity.h"

class Game;
class Sprite;

class Asteroid : public BaseEntity
{
private:
	Sprite* sprite;
	float duration;

public:
	Asteroid(Game* aGame);

	// Inherited via BaseEntity
	void update(sf::Time& elapsed) override;
	void render() override;
	void onCollision(BaseEntity* entity) override;
	sf::FloatRect getBounds() override;
};

