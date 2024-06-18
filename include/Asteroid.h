#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "./BaseEntity.h"

class Game;
class Sprite;

class Asteroid : public BaseEntity
{
private:
	std::vector<Sprite*> sprite;
	float duration;
	float sizeMultipler;

	size_t animationIndex;

	bool isHit;
	float direction;

public:
	Asteroid(Game* aGame);

	void initialize(float aSizeMultipler);
	void setDestroy();

	bool canHit() const;

	void setPosition(const sf::Vector2f aPosition);
	void setPosition(const float x, const float y);
	sf::Vector2f getPosition() const;

	// Inherited via BaseEntity
	void update(sf::Time& elapsed) override;
	void Move(sf::Time& elapsed);
	void render() override;
	void onCollision(BaseEntity* entity) override;
	sf::FloatRect getBounds() override;

private:
	void updateDestroy(sf::Time& elapsed);
	void wrapPlayer();

	sf::Vector2f getRandomPosition(const sf::RenderWindow& window) const;
	float getRandomDirection() const;

};

