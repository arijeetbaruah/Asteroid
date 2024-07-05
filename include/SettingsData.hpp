#pragma once

const std::string settingsSaveFile = "../save/settings.bin";

struct SettingsData
{
    float masterVolume = 100;
    float musicVolume = 100;

    float getMusicVolumeNormalize() const
    {
        return (masterVolume / 100) * (musicVolume / 100) * 100;
    }
};
