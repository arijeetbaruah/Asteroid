#include "../include/MainMenuGameState.h"
#include "../include/Game.h"
#include "../include/AssetManager.h"

MainMenuGameState::MainMenuGameState(Game* mGame): game(mGame)
{
}

void MainMenuGameState::enter()
{
	mainMenuFont = game->assetManager->GetFont("PlayfairDisplay.ttf");
}

void MainMenuGameState::update(sf::Time elapsed)
{
}

void MainMenuGameState::render(sf::RenderWindow& window)
{
	sf::CircleShape shape(50.f);
	window.draw(shape);
}

void MainMenuGameState::exit()
{
}
