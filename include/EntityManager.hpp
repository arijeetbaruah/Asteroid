#pragma once
#include <SFML/Graphics.hpp>

class Game;
class BaseEntity;

class EntityManager
{
private:
	Game* game;

	std::vector<std::shared_ptr<BaseEntity>> registry;

public:
	EntityManager(Game* aGame);

	void addEntity(std::shared_ptr<BaseEntity> entity);
	void clearEntities();

	void update(sf::Time& elapsed);
	void render();
};

