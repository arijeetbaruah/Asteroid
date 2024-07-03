#pragma once
#include <SFML/Graphics.hpp>

class Game;

class BaseEntity
{
protected:
	Game* game;
	bool active;

public:
	BaseEntity(Game* aGame);

	void setActive(bool aActive);
	bool isActive();

	virtual void update(sf::Time& elapsed) = 0;
	virtual void render() = 0;

	virtual void onCollision(std::shared_ptr<BaseEntity> entity) = 0;
	void calculateCollision(std::shared_ptr<BaseEntity> entity);

	virtual sf::FloatRect getBounds() = 0;
};

