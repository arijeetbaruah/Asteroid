#pragma once

#include <SFML/Graphics.hpp>

class Game;

class Trail {
private:
	Game* game;

	sf::CircleShape shape;
	float timer;
	bool isEnable;
public:
	Trail(Game* aGame);

	void reset();
	void setPosition(sf::Vector2f aPosition);
	bool getEnable() const;

	void update(sf::Time& elapsed);
	void render();
};

