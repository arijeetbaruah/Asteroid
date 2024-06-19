#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class BaseGameState;
class GameStateMachine;
class MainMenuGameState;
class GameOverGameState;
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
    std::shared_ptr<GameOverGameState> gameOverGameState;
    std::shared_ptr<GameGameState> gameGameState;
    sf::Vector2<unsigned int> windowSize;

public:
    Game(sf::Vector2<unsigned int> aWindowSize, std::string name);

    void run();
    void gotoMainMenu();
    void StartGame();
    void GameOver();
    void setState(std::shared_ptr<BaseGameState> state);
    std::shared_ptr<EntityManager> getEntityManager() const;

    std::shared_ptr<BaseGameState> getCurrentGameState() const;

public:
    void handleInput();
    void update(sf::Time& elapsed);
    void render();
};

