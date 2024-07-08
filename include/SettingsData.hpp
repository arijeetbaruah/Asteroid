#pragma once

#include "yaml-cpp/yaml.h"

const std::string settingsSaveFile = "../save/settings.sav";

struct SettingsData
{
    float masterVolume = 100;
    float musicVolume = 100;

    float getMusicVolumeNormalize() const
    {
        return (masterVolume / 100) * (musicVolume / 100) * 100;
    }

    static SettingsData fromYAML(std::string yamlStr)
    {
        YAML::Node config = YAML::Load(yamlStr);
        SettingsData data;
        data.masterVolume = config["masterVolume"].as<float>();
        data.musicVolume = config["musicVolume"].as<float>();

        return data;
    }

    std::string toYAML()
    {
        YAML::Node config;
        config["masterVolume"] = masterVolume;
        config["musicVolume"] = musicVolume;

        YAML::Emitter out;
        out << config;

        return out.c_str();
    }
};
