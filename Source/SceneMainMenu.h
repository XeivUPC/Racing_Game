#pragma once

#include "Globals.h"
#include "ModuleScene.h"

#include "p2Point.h"

#include "raylib.h"
#include <vector>

class UIButton;

class SceneMainMenu : public ModuleScene
{
public:
	SceneMainMenu(Application* app, bool start_enabled = true);
	~SceneMainMenu();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	Rectangle  backgroundTextureRec = { 0, 0, 640, 360 };

	UIButton* play_button = nullptr;
	Rectangle  play_buttonTextureRec = { 32, 192, 192, 64 };

	UIButton* settings_button = nullptr;
	Rectangle  settings_buttonTextureRec = { 32, 72, 288, 64};

};
