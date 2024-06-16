#pragma once

#include <SFML/Graphics.hpp>
#include "./BaseEntity.h"

class Game;
class Sprite;

class Player : public BaseEntity
{
private:
	Sprite* sprite;

	sf::Vector2f movementDirection;
	bool isMoving;
	bool isRotating;

public:
	Player(Game* mGame);
	~Player();

	sf::Vector2f getForwardVector() const;

	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);
	sf::Vector2f getPosition() const;

	float getRotation() const;

	void move(sf::Vector2f position);
	void move(float x, float y);

	void rotate(float angle);

	void setScale(float x, float y);
	void setScale(sf::Vector2f scale);

	void handleInput();

	// Inherited via BaseEntity
	void render() override;
	void update(sf::Time& elapsed) override;
	void onCollision(BaseEntity* entity) override;
	sf::FloatRect getBounds() override;

private:
	void wrapPlayer();
	void movementInput();
	void shootInput();

	void Shoot();
};
