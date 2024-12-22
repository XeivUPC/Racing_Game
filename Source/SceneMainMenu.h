#pragma once

#include "Globals.h"
#include "ModuleScene.h"

#include "p2Point.h"

#include "raylib.h"
#include <vector>

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
