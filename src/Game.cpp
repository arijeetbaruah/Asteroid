#include "../include/Game.hpp"
#include "../include/BaseGameState.hpp"
#include "../include/GameStateMachine.hpp"
#include "../include/GameOverGameState.hpp"
#include "../include/MainMenuGameState.hpp"
#include "../include/SettingsGameState.hpp"
#include "../include/EntityManager.hpp"
#include "../include/GameGameState.hpp"
#include "../include/FileReadWrite.hpp"

#include "boost/json.hpp"
#include <iostream>
#include <sstream>
#include <vector>

#include "spdlog/spdlog.h"

// for string delimiter
std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

Game::Game(sf::Vector2<unsigned int> aWindowSize, std::string name):
	window(sf::VideoMode(aWindowSize.x, aWindowSize.y), name),
	stateMachine(std::make_shared<GameStateMachine>(this)),
	mainMenuState(std::make_shared<MainMenuGameState>(this)),
    gameGameState(std::make_shared<GameGameState>(this)),
    settingsGameState(std::make_shared<SettingsGameState>(this)),
    gameOverGameState(std::make_shared<GameOverGameState>(this)),
    fileReadWrite(std::make_shared<FileReadWrite>()),
    entityManager(std::make_shared<EntityManager>(this)),
	windowSize(aWindowSize)
{
	window.setFramerateLimit(144);

	setState(mainMenuState);

    if (fileReadWrite->exists(settingsSaveFile))
    {
        std::vector<std::string> data = split(fileReadWrite->readFile(settingsSaveFile), ",");
        settingsData.masterVolume = std::stof(data[0]);
        settingsData.musicVolume = std::stof(data[1]);
    }
    else
    {
        fileReadWrite->createFile(settingsSaveFile, "100,100");
        spdlog::error("file not found");
    }
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

void Game::gotoSettings()
{
    setState(settingsGameState);
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

std::shared_ptr<FileReadWrite> Game::getFileReadWrite() const
{
    return fileReadWrite;
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
