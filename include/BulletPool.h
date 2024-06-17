#pragma once

#include <SFML/Graphics.hpp>
#include<vector>

class Game;
class Bullet;

class BulletPool
{
public:
	BulletPool(Game* aGame, size_t aSize, sf::Color aColor, bool aHitPlayer);
	Bullet* getBullet();

private:
	std::vector<Bullet*> bullets;
};

