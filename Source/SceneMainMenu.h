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

private:

	void ClickPlay();
	void ClickSettings();

	void OnMouseOverPlay();
	void OnMouseOverSettings();

	Texture2D* backgroundTexture = nullptr;
	Rectangle  backgroundTextureRec = { 0, 0, 640, 360 };

	UIButton* play_button = nullptr;
	Texture2D* play_buttonTexture = nullptr;
	Texture2D* play_buttonTexture_hover = nullptr;
	Rectangle  play_buttonTextureRec = { (32 * 2), (192 * 2 ), 192 * 2, 64 * 2 };

	UIButton* settings_button = nullptr;
	Texture2D* settings_buttonTexture = nullptr;
	Texture2D* settings_buttonTexture_hover = nullptr;
	Rectangle  settings_buttonTextureRec = { (32 * 2 ), (272 * 2 ), 288 * 2, 64 * 2 };

};
