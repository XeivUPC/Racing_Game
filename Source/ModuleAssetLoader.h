#pragma once

#include "Module.h"
class ModuleAssetLoader : public Module
{
public:
	ModuleAssetLoader(Application* app, bool start_enabled = true);
	~ModuleAssetLoader();

	bool Init();

	Font basicFont;
	Font agencyB;
	Font titleFont;

	int audioMotorId = -1;
	int audioMainMenuMusicId = -1;
	int audioMainMenuMarioWiiMusicId = -1;
	int audioClickId = -1;
	int audioEngineId = -1;
	int audioEngineStartId = -1;
};

