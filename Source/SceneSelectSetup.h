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
	enum MAPS {
		MAP1,
		MAP2,
		MAP3
	};

	// Choosing Car Type
	enum VEHICLES {
		NONE,
		CAR,
		MOTO,
		TRUCK,
		END
	};


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

	void ClickFINISH();
	void OnMouseOverFINISH();

	void ClickCarRightArrow();

	void ClickCarLeftArrow();

	Texture2D* car_bg_texture = nullptr;
	Rectangle  car_bg_textureRec = { 0, 0, 640, 360 };

	UIButton* finish_car_button = nullptr;
	Rectangle finish_car_button_textureRec = { (282 * 2), (240 * 2), 304 * 2, 64 * 2 };
	Texture2D* finish_car_button_texture_hover = nullptr;
	Rectangle  finish_car_button_texture_hover_section = { 0, 0, 304, 64 };
	Vector2 finish_car_button_textOffset = { 80, 7 };

	Vector2 car_name_text_pos = { 141 * 2 , 283 * 2 };

	UIButton* car_arrow_right = nullptr;
	Rectangle car_arrow_right_rec = { (233 * 2), (164 * 2), 15 * 2, 13 * 2 };
	UIButton* car_arrow_left = nullptr;
	Rectangle car_arrow_left_rec = { (36 * 2), (164 * 2), 15 * 2, 13 * 2 };

	bool isCarChosen = false;
	VEHICLES currentVEHICLE = VEHICLES::CAR;
	VEHICLES finalVEHICLE = VEHICLES::NONE;

};