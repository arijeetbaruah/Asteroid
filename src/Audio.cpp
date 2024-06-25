#include "../include/audio.hpp"

#include "spdlog/spdlog.h"

#if _DEBUG
#define ASSET_SPRITES "../assets/sounds/"
#else
#define ASSET_SPRITES "./assets/sounds/"
#endif

Audio::Audio(std::string aAudioFile)
{
    if (!audioBuffer.loadFromFile(ASSET_SPRITES + aAudioFile)) {
        spdlog::error("Error loading sounds/" + aAudioFile);
        return;
    }
    else {
        spdlog::info("loading sounds/" + aAudioFile);
        audio.setBuffer(audioBuffer);
    }
}

void Audio::play()
{
    audio.play();
}

void Audio::stop()
{
    audio.stop();
}

void Audio::pause()
{
    audio.pause();
}

void Audio::setPitch(const float aPitch)
{
    audio.setPitch(aPitch);
}

float Audio::getPitch() const
{
    return audio.getPitch();
}

void Audio::setVolume(const float aVolume)
{
    audio.setVolume(aVolume);
}

float Audio::getVolume() const
{
    return audio.getVolume();
}

void Audio::setLoop(const bool aLoop)
{
    audio.setLoop(aLoop);
}

bool Audio::getLoop() const
{
    return audio.getLoop();
}

void Audio::setPlayingOffset(sf::Time aOffset)
{
    audio.setPlayingOffset(aOffset);
}

sf::Time Audio::setPlayingOffset() const
{
    return audio.getPlayingOffset();
}
