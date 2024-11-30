#pragma once

#include "Module.h"
class ModuleAssetLoader : public Module
{
public:
	ModuleAssetLoader(Application* app, bool start_enabled = true);
	~ModuleAssetLoader();

	bool Init();
};

