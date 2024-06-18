#pragma once

#include <SFML/Graphics.hpp>
#include "./BaseEntity.h"

class Bullet : public BaseEntity
{
private:
	sf::CircleShape circle;
	sf::Vector2f direction;

	float lifeSpan;
	bool hitPlayer;

public:
	Bullet(Game* aGame, sf::Color aColor, bool aHitPlayer);

	void reset();
	bool canHitPlayer() const;

	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f aPosition);
	void setPosition(float x, float y);
	void setDirection(sf::Vector2f aDirection);

	// Inherited via BaseEntity
	void render() override;
	void update(sf::Time& elapsed) override;
	void onCollision(BaseEntity* entity) override;
	sf::FloatRect getBounds() override;

private:
	void wrapPlayer();
};

