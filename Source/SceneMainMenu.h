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


	Texture2D* backgroundTexture = nullptr;
	Rectangle  backgroundTextureRec = { 0, 0, 640, 360 };

	UIButton* play_button = nullptr;
	UIButton* settings_button = nullptr;

	Texture2D* btn_texture = nullptr;
	Rectangle btn_rect = { 0,0,304,71 };
	Rectangle btn_rect_hover = { 305,0,305,71 };
	Rectangle btn_rect_pressed = { 305 * 2,0,305,71 };
	
};
