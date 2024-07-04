#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include "./SettingsData.hpp"

class BaseGameState;
class GameStateMachine;
class MainMenuGameState;
class GameOverGameState;
class SettingsGameState;
class GameGameState;
class FileReadWrite;
class EntityManager;

class Game
{
private:
    std::shared_ptr<GameStateMachine> stateMachine;
    std::shared_ptr<EntityManager> entityManager;
    std::shared_ptr<FileReadWrite> fileReadWrite;

public:
    sf::RenderWindow window;
    SettingsData settingsData;

private:
    std::shared_ptr<MainMenuGameState> mainMenuState;
    std::shared_ptr<GameOverGameState> gameOverGameState;
    std::shared_ptr<SettingsGameState> settingsGameState;
    std::shared_ptr<GameGameState> gameGameState;
    sf::Vector2<unsigned int> windowSize;

public:
    Game(sf::Vector2<unsigned int> aWindowSize, std::string name);

    void run();
    void gotoMainMenu();
    void gotoSettings();
    void StartGame();
    void GameOver();
    void setState(std::shared_ptr<BaseGameState> state);
    std::shared_ptr<EntityManager> getEntityManager() const;

    std::shared_ptr<BaseGameState> getCurrentGameState() const;
    std::shared_ptr<FileReadWrite> getFileReadWrite() const;

public:
    void handleInput();
    void update(sf::Time& elapsed);
    void render();
};

