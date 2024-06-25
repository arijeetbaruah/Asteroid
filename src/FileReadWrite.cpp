#include "../include/FileReadWrite.hpp"
#include <iostream>
#include <fstream>
#include <spdlog/spdlog.h>

#include "../include/SettingData.hpp"

const std::string SETTINGS_FILE = "../save/settings.dat";

void FileReadWrite::SaveSettings(SettingData data)
{
	std::fstream outfile;
	outfile.open(SETTINGS_FILE, std::ios::out | std::ios::binary | std::ios::trunc);

	if (!outfile)
	{
		outfile.write(reinterpret_cast<char*>(&data), sizeof(SettingData));
		outfile.close();
		spdlog::info("Settings Saved!!");
	}
	else {
		spdlog::error("Unable to save settings file");
	}
}

bool FileReadWrite::ReadSettings(SettingData& data)
{
	std::ifstream infile(SETTINGS_FILE, std::ios::in | std::ios::binary);
	
	if (infile.is_open())
	{
		infile.read(reinterpret_cast<char*>(&data), sizeof(SettingData));
		infile.close();

		return true;
	}

	spdlog::error("Unable to open settings file");
	return false;
}
