#pragma once

#include "Globals.h"
#include "ModuleScene.h"

#include "p2Point.h"

#include "raylib.h"
#include <vector>

class UIButton;

class SceneSelectSetup : public ModuleScene
{
public:
	SceneSelectSetup(Application* app, bool start_enabled = false);
	~SceneSelectSetup();

	bool Start();
	update_status Update();
	bool Render();
	bool CleanUp();

private:

	void ClickRACE();
	void ClickBOOM();

	void OnMouseOverRACE();
	void OnMouseOverBOOM();

	Texture2D* backgroundTexture = nullptr;
	Rectangle  backgroundTextureRec = { 0, 0, 640, 360 };

	Texture2D* buttons_texture = nullptr;
	Rectangle  buttons_textureRec = { 0, 0, 640, 360 };

	Texture2D* buttons_texture_hover = nullptr;
	Rectangle  buttons_texture_hover_section = { 0, 0, 400, 64 };

	UIButton* race_button = nullptr;
	Rectangle race_buttonTextureRec = { (120 * 2), (107 * 2), 400 * 2, 64 * 2 };

	UIButton* boom_button = nullptr;
	Rectangle boom_buttonTextureRec = { (120 * 2), (206 * 2), 400 * 2, 64 * 2 };

	Vector2 buttonsText_Offset = { 48, 7 };
};
