#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio.hpp>

class Music
{
private:
	sf::Music music;

public:
	Music(std::string musicFile);

	void play();
	void stop();
	void pause();

	void setPitch(const float aPitch);
	float getPitch() const;

	void setVolume(const float aVolume);
	float getVolume() const;
	
	void setLoop(const bool aLoop);
	bool getLoop() const;

	void setPlayingOffset(const sf::Time offset);
	sf::Time setPlayingOffset() const;
};

