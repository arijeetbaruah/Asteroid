#include "../include/BulletPool.h"
#include "../include/Game.h"
#include "../include/EntityManager.h"
#include "../include/Bullet.h"

BulletPool::BulletPool(Game* aGame, size_t aSize, sf::Color aColor, bool aHitPlayer) {
    // Initialize bullets in the pool
    for (size_t index = 0; index < aSize; index++)
    {
        Bullet* bullet = new Bullet(aGame, aColor, aHitPlayer);
        bullets.push_back(bullet);
        aGame->getEntityManager()->addEntity(bullet);
    }
}

Bullet* BulletPool::getBullet() {
    for (auto bullet : bullets) {
        if (!bullet->isActive()) {
            return bullet;
        }
    }
    return nullptr; // No available bullets
}
