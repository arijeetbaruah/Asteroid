#pragma once
#include <SFML/Graphics.hpp>

class BaseGameState;
class GameStateMachine;
class MainMenuGameState;
class AssetManager;

class Game
{
private:
    std::shared_ptr<GameStateMachine> stateMachine;

private:
    std::shared_ptr<MainMenuGameState> mainMenuState;

public:
    std::shared_ptr<AssetManager> assetManager;

public:
    Game();

    void setState(std::shared_ptr<BaseGameState> state);
    void update(sf::Time& elapsed);
    void render(sf::RenderWindow& window);
};

