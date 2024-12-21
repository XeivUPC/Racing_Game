#pragma once

#include "Module.h"

class Application;

class ModuleOptions : public Module {
private: 

	bool enabled;

	Vector2 sliderVolumePosition = {0,0};
	
public:

	ModuleOptions(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleOptions();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};