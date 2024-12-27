#pragma once

#include "ModuleScene.h"

class UIButton;

class SceneMainMenu : public ModuleScene
{
public:
	SceneMainMenu(Application* app, bool start_enabled = true);
	~SceneMainMenu();

	bool Start();
	update_status Update();
	bool Render();
	bool CleanUp();

private:

	void ClickPlay();
	void ClickSettings();

	void OnMouseOverPlay();
	void OnMouseOverSettings();

	Texture2D* backgroundTexture = nullptr;
	Rectangle  backgroundTextureRec = { 0, 0, 640, 360 };

	UIButton* play_button = nullptr;
	Texture2D* play_buttonTexture_hover = nullptr;
	Rectangle  play_buttonTextureRec = { (32 * 2), (192 * 2 ), 248 * 2, 64 * 2 };
	Rectangle  play_button_section = { 0, 0, 256, 64};

	UIButton* settings_button = nullptr;
	Texture2D* settings_buttonTexture_hover = nullptr;
	Rectangle  settings_buttonTextureRec = { (32 * 2 ), (272 * 2 ), 304 * 2, 64 * 2 };
	Rectangle  settings_button_section = { 0, 0, 304, 64};

	Vector2 buttonsText_Offset = { 48, 7 };
};
