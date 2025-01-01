#pragma once
#include "Module.h"
#include <unordered_map>
#include <string>


class ModuleUserPreferences : public Module
{
public:
	ModuleUserPreferences(Application* app, bool start_enabled=true);
	~ModuleUserPreferences();

	bool Init();
	bool CleanUp();
	void SaveUserPreferences();

private:
	void LoadUserPreferences();

	std::string configPath = "Assets/Data/game_settings.xml";
};

