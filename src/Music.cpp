#include "../include/Music.hpp"

#include "spdlog/spdlog.h"

#if _DEBUG
#define ASSET_SPRITES "../assets/musics/"
#else
#define ASSET_SPRITES "./assets/musics/"
#endif

Music::Music(std::string aMusicFile)
{
    if (!music.openFromFile(ASSET_SPRITES + aMusicFile)) {
        spdlog::error("Error loading background image");
        return;
    }
}

void Music::play()
{
    music.play();
}

void Music::stop()
{
    music.stop();
}

void Music::pause()
{
    music.pause();
}

void Music::setPitch(const float aPitch)
{
    music.setPitch(aPitch);
}

float Music::getPitch() const
{
    return music.getPitch();
}

void Music::setVolume(const float aVolume)
{
    music.setVolume(aVolume);
}

float Music::getVolume() const
{
    return music.getVolume();
}

void Music::setLoop(const bool aLoop)
{
    music.setLoop(aLoop);
}

bool Music::getLoop() const
{
    return music.getLoop();
}

void Music::setPlayingOffset(sf::Time aOffset)
{
    music.setPlayingOffset(aOffset);
}

sf::Time Music::setPlayingOffset() const
{
    return music.getPlayingOffset();
}
