#include "../include/BulletPool.hpp"
#include "../include/Game.hpp"
#include "../include/EntityManager.hpp"
#include "../include/Bullet.hpp"

BulletPool::BulletPool(Game* aGame, size_t aSize, sf::Color aColor, bool aHitPlayer) {
    // Initialize bullets in the pool
    for (size_t index = 0; index < aSize; index++)
    {
        std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(aGame, aColor, aHitPlayer);
        bullets.push_back(bullet);
        aGame->getEntityManager()->addEntity(bullet);
    }
}

std::shared_ptr<Bullet> BulletPool::getBullet() {
    for (auto bullet : bullets) {
        if (!bullet->isActive()) {
            return bullet;
        }
    }
    return nullptr; // No available bullets
}
