#include "../include/AssetManager.h"
#include "spdlog/spdlog.h"
#include <filesystem>

sf::Font& AssetManager::GetFont(std::string file)
{
    sf::Font font;
    spdlog::info("loading font " + file);

    std::string filePath = "../assets/fonts/" + file;

    if (!std::filesystem::exists(filePath)) {
        spdlog::error("Error: Font file not found at " + filePath);
        return font;
    }

    if (!font.loadFromFile(filePath))
    {
        spdlog::error("Failed to load " + file);
    }

    return font;
}
