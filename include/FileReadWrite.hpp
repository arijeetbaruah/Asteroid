#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

struct SettingData;

class FileReadWrite
{
public:
	void SaveSettings(SettingData data);
	bool ReadSettings(SettingData& data);
};

