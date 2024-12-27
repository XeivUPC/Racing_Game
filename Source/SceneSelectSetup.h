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

	// Choosing Modes
	enum class MODES {
		NONE,
		RACE,
		BOOM
	};

	// Choosing Map

	// Choosing Car Type


private:

	// Choosing Modes
	void ClickRACE();
	void ClickBOOM();

	void OnMouseOverRACE();
	void OnMouseOverBOOM();

	Texture2D* backgroundTexture = nullptr;
	Rectangle  backgroundTextureRec = { 0, 0, 640, 360 };

	Texture2D* buttons_texture = nullptr;
	Rectangle  buttons_textureRec = { 0, 0, 640, 360 };

	Texture2D* buttons_texture_hover = nullptr;
	Rectangle  buttons_texture_hover_section = { 0, 0, 304, 64 };

	UIButton* race_button = nullptr;
	Rectangle race_buttonTextureRec = { (176 * 2), (107 * 2), 304 * 2, 64 * 2 };

	UIButton* boom_button = nullptr;
	Rectangle boom_buttonTextureRec = { (176 * 2), (206 * 2), 304 * 2, 64 * 2 };

	Vector2 buttonsText_Offset = { 0, 7 };

	Vector2 description_middle_pos = { 486 * 2, 34 * 2 };

	bool isModeChosen = false;
	MODES currentMode = MODES::NONE;

	// Choosing Map
	
	// Choosing Car Type

};
