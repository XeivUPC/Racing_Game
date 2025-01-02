#pragma once

#include "ModuleScene.h"

class UIButton;

class SceneResults : public ModuleScene
{
public:
	SceneResults(Application* app, bool start_enabled = true);
	~SceneResults();

	bool Start();
	update_status Update();
	bool Render();
	bool CleanUp();

private:

	void ClickNext();
	void OnMouseOverNext();

	Texture2D* backgroundTexture = nullptr;
	Rectangle  backgroundTextureRec = { 0, 0, 1280, 720 };

	UIButton* next_button = nullptr;
	Texture2D* next_buttonTexture_hover = nullptr;
	Rectangle  next_buttonTextureRec = { (SCREEN_WIDTH / 2), (72 * 8), 66 * 8, 12 * 8 };
	Rectangle  next_button_section = { 0, 0, 66 * 8, 12 * 8 };

	Vector2 buttonsText_Offset = { 48, 7 };
};
