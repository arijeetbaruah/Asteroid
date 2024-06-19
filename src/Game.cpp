#include "../include/Game.h"
#include "../include/BaseGameState.h"
#include "../include/GameStateMachine.h"
#include "../include/GameOverGameState.h"
#include "../include/MainMenuGameState.h"
#include "../include/EntityManager.h"
#include "../include/GameGameState.h"

Game::Game(sf::Vector2<unsigned int> aWindowSize, std::string name):
	window(sf::VideoMode(aWindowSize.x, aWindowSize.y), name),
	stateMachine(std::make_shared<GameStateMachine>(this)),
	mainMenuState(std::make_shared<MainMenuGameState>(this)),
    gameGameState(std::make_shared<GameGameState>(this)),
    gameOverGameState(std::make_shared<GameOverGameState>(this)),
    entityManager(std::make_shared<EntityManager>(this)),
	windowSize(aWindowSize)
{
	window.setFramerateLimit(144);

	setState(mainMenuState);
}

void Game::run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        handleInput();
        update(elapsed);

        window.clear();
        render();
        window.display();
    }
}

void Game::gotoMainMenu()
{
    setState(mainMenuState);
}

void Game::setState(std::shared_ptr<BaseGameState> state)
{
    entityManager->clearEntities();
	stateMachine->setState(state);
}

std::shared_ptr<EntityManager> Game::getEntityManager() const
{
    return entityManager;
}

std::shared_ptr<BaseGameState> Game::getCurrentGameState() const
{
    return stateMachine->getCurrentState();
}

void Game::StartGame()
{
	setState(gameGameState);
}

void Game::GameOver()
{
    setState(gameOverGameState);
}

void Game::handleInput()
{
    for (auto event = sf::Event{}; window.pollEvent(event);)
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
            return;
        }

        stateMachine->handleInput(event);
    }
}

void Game::update(sf::Time& elapsed)
{
	stateMachine->update(elapsed);
    entityManager->update(elapsed);
}

void Game::render()
{
    stateMachine->render();
    entityManager->render();
}
