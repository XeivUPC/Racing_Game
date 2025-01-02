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
	Rectangle  backgroundTextureRec = { 0, 0, 640, 360 };

	UIButton* next_button = nullptr;
	Texture2D* next_buttonTexture_hover = nullptr;
	Rectangle  next_buttonTextureRec = { (32 * 2), (192 * 2), 248 * 2, 64 * 2 };
	Rectangle  next_button_section = { 0, 0, 256, 64 };

	Vector2 buttonsText_Offset = { 48, 7 };
};
