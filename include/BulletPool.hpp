#pragma once

#include <SFML/Graphics.hpp>
#include<vector>

class Game;
class Bullet;

class BulletPool
{
public:
	BulletPool(Game* aGame, size_t aSize, sf::Color aColor, bool aHitPlayer);
	std::shared_ptr<Bullet> getBullet();

private:
	std::vector<std::shared_ptr<Bullet>> bullets;
};

