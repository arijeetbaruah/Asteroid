#pragma once
#include <SFML/Graphics.hpp>

class BaseGameState;
class GameStateMachine;
class MainMenuGameState;
class GameGameState;
class EntityManager;

class Game
{
private:
    std::shared_ptr<GameStateMachine> stateMachine;
    std::shared_ptr<EntityManager> entityManager;

public:
    sf::RenderWindow window;

private:
    std::shared_ptr<MainMenuGameState> mainMenuState;
    std::shared_ptr<GameGameState> gameGameState;
    sf::Vector2<unsigned int> windowSize;

public:
    Game(sf::Vector2<unsigned int> aWindowSize, std::string name);

    void run();
    void StartGame();
    void setState(std::shared_ptr<BaseGameState> state);
    std::shared_ptr<EntityManager> getEntityManager() const;

public:
    void update(sf::Time& elapsed);
    void render();
};

