#pragma once

#include "Globals.h"
#include "ModuleScene.h"

#include "p2Point.h"

#include "raylib.h"
#include <vector>

class ModuleMainMenu : public ModuleScene
{
public:
	ModuleMainMenu(Application* app, bool start_enabled = true);
	~ModuleMainMenu();

	bool Start();
	update_status Update();
	bool CleanUp();
	void Test();

public:

};
