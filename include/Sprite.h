#pragma once

#include <SFML/Graphics.hpp>

class Game;

class Sprite
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	Game* game;

public:
	Sprite(Game* game, std::string aTextureFile);

	sf::FloatRect GetBounds() const;
	sf::FloatRect GetLocalBounds() const;

	void setScale(sf::Vector2f scale);
	void setScale(float x, float y);

	void setTextureRect(sf::IntRect rect);

	void setPosition(sf::Vector2f aPosition);
	void setPosition(float x, float y);
	sf::Vector2f getPosition() const;

	float getRotation() const;

	void move(sf::Vector2f aPosition);
	void move(float x, float y);
	
	void rotation(float angle);

	void update(sf::Time& elapsed);
	void render();
};

