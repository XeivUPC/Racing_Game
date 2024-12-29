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
		NO_MODE,
		RACE,
		BOOM
	};

	// Choosing Car Type
	enum VEHICLES {
		NO_VEHICLE,
		CAR,
		MOTO,
		TRUCK,
		END_VEHICLE
	};

	// Choosing Map
	enum MAPS {
		NO_MAP,
		MAP1,
		MAP2,
		MAP3,
		END_MAP
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

	Vector2 description_middle_pos = { 483 * 2, 34 * 2 };

	bool isModeChosen = false;
	MODES currentMode = MODES::NO_MODE;
	
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
	VEHICLES finalVEHICLE = VEHICLES::NO_VEHICLE;

	// Choosing Map
	void ClickMapFINISH();
	void OnMouseOverMapFINISH();

	void ClickMapRightArrow();

	void ClickMapLeftArrow();

	Texture2D* map_bg_texture = nullptr;
	Rectangle  map_bg_textureRec = { 0, 0, 640, 360 };

	UIButton* finish_map_button = nullptr;
	Rectangle finish_map_button_textureRec = { (222 * 2), (283 * 2), 200 * 2, 32 * 2 };
	Texture2D* finish_map_button_texture_hover = nullptr;
	Rectangle  finish_map_button_texture_hover_section = { 0, 0, 200, 32 };
	Vector2 finish_map_button_textOffset = { 80, 7 };

	Vector2 map_name_text_pos = { SCREEN_WIDTH/2 , 84 * 2 };
	Vector2 map_finish_text_pos = { SCREEN_WIDTH/2 , 284 * 2 };

	UIButton* map_arrow_right = nullptr;
	Rectangle map_arrow_right_rec = { (462 * 2), (190 * 2), 15 * 2, 13 * 2 };
	UIButton* map_arrow_left = nullptr;
	Rectangle map_arrow_left_rec = { (167 * 2), (190 * 2), 15 * 2, 13 * 2 };

	bool isMapChosen = false;
	MAPS currentMAP = MAPS::MAP1;
	MAPS finalMAP = MAPS::NO_MAP;
};