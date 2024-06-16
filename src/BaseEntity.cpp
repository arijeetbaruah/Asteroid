#include "../include/BaseEntity.h"
#include "../include/Game.h"

BaseEntity::BaseEntity(Game* aGame): game(aGame), active(true)
{
}

void BaseEntity::setActive(bool aActive)
{
	active = aActive;
}

bool BaseEntity::isActive()
{
	return active;
}

void BaseEntity::calculateCollision(BaseEntity* entity)
{
	if (getBounds().intersects(entity->getBounds()))
	{
		onCollision(entity);
	}
}
