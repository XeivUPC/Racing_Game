#pragma once

#include "ModuleScene.h"

class SceneMainMenu : public ModuleScene
{
public:
	SceneMainMenu(Application* app, bool start_enabled = true);
	~SceneMainMenu();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

};
