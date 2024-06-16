#pragma once
#include <SFML/Graphics.hpp>

class Game;
class BaseEntity;

class EntityManager
{
private:
	Game* game;

	std::vector<BaseEntity*> registry;

public:
	EntityManager(Game* aGame);

	void AddEntity(BaseEntity* entity);

	void update(sf::Time& elapsed);
	void render();
};

