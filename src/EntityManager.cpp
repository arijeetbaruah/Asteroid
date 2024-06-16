#include "../include/EntityManager.h"
#include "../include/Game.h"
#include "../include/BaseEntity.h"

EntityManager::EntityManager(Game* aGame) : game(aGame)
{
}

void EntityManager::AddEntity(BaseEntity* entity)
{
	registry.push_back(entity);
}

void EntityManager::update(sf::Time& elapsed)
{
	// Check Collision
	for (size_t i = 0; i < registry.size(); i++)
	{
		if (registry[i]->isActive())
		{
			for (size_t j = 0; j < registry.size(); j++)
			{
				if (registry[i]->isActive() && registry[j]->isActive())
				{
					registry[i]->calculateCollision(registry[j]);
				}
			}
		}
	}

	for (size_t i = 0; i < registry.size(); i++)
	{
		registry[i]->update(elapsed);
	}
}

void EntityManager::render()
{
	for (size_t i = 0; i < registry.size(); i++)
	{
		registry[i]->render();
	}
}