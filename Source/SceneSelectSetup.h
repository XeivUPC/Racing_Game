#pragma once

#include "Globals.h"
#include "ModuleScene.h"

#include "p2Point.h"

#include "raylib.h"
#include <vector>
#include <string>


class UIButton;
class Animator;

using namespace std;

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


private:


	////NEW UPDATE
	struct MapTypeData {
		string name;
		string mapPath;
		string imagePreviewId;

		MapTypeData(const string& name, const string& mapPath, const string& imagePreviewId)
			: name(name), mapPath(mapPath), imagePreviewId(imagePreviewId)
		{
		}
	};

	struct VehicleTypeData {
		string name;
		string prefix;
		float velocity;
		float control;
		float drift;

		VehicleTypeData(const string& name, const string& prefix, float velocity, float control, float drift)
			: name(name), prefix(prefix), velocity(velocity), control(control), drift(drift)
		{
		}
	};

	string setupDataPath = "Assets/Data/game_setup_options.xml";
	void LoadSetUpInformation();
	vector<MapTypeData> maps;
	Texture* mapPreviewTexture = nullptr;
	Rectangle mapPreviewTextureRec = { 0,0, 256,145};

	vector<VehicleTypeData> vehicles;

	int currentSelectedMap = 0;
	int currentSelectedVehicle = 0;


	/////////////////////////////////////////////////


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

	void ClickCarRightArrow();
	void OverCarRightArrow();
	void ExitCarRightArrow();

	void ClickCarLeftArrow();
	void OverCarLeftArrow();
	void ExitCarLeftArrow();

	Texture2D* car_bg_texture = nullptr;
	Rectangle  car_bg_textureRec = { 0, 0, 640, 360 };

	UIButton* finish_car_button = nullptr;
	Rectangle finish_car_button_textureRec = { (243 * 2), (272 * 2), 152 * 2, 36 * 2 };

	Texture2D* btn_texture = nullptr;
	Rectangle btn_rect = { 0,0,304,71 };
	Rectangle btn_rect_hover = { 305,0,305,71 };
	Rectangle btn_rect_pressed = { 305 * 2,0,305,71 };

	Vector2 velocity_text_pos = { 143 * 2 , 182 * 2 };
	Vector2 control_text_pos = { SCREEN_WIDTH/2 , 182 * 2 };
	Vector2 drift_text_pos = { 495 * 2 , 182 * 2 };

	Vector2 car_name_text_pos = { SCREEN_WIDTH/2 , 226 * 2 };
	UIButton* car_arrow_right = nullptr;
	Rectangle car_arrow_right_rec = { (446 * 2), (239 * 2) - 13, 15 * 2, 13 * 2 };
	UIButton* car_arrow_left = nullptr;
	Rectangle car_arrow_left_rec = { (192 * 2) - 15*2, (239 * 2) - 13, 15 * 2, 13 * 2 };

	Texture2D* arrows_texture = nullptr;
	Animator* arrowRightSetupCarAnimator = nullptr;
	Animator* arrowLeftSetupCarAnimator = nullptr;

	bool justClickedarrowRightSetupCar = false;
	bool justClickedarrowLeftSetupCar = false;

	bool isCarChosen = false;

	// Choosing Map
	void ClickMapFINISH();

	void OnMouseOverMapFINISH();

	void ClickMapRightArrow();
	void OverMapRightArrow();
	void ExitMapRightArrow();

	void ClickMapLeftArrow();
	void OverMapLeftArrow();
	void ExitMapLeftArrow();

	Texture2D* map_bg_texture = nullptr;
	Rectangle  map_bg_textureRec = { 0, 0, 640, 360 };

	UIButton* finish_map_button = nullptr;
	Rectangle finish_map_button_textureRec = { (243 * 2), (272 * 2), 152 * 2, 36 * 2 };

	Vector2 map_name_text_pos = { SCREEN_WIDTH/2 , 84 * 2 };
	Vector2 map_finish_text_pos = { SCREEN_WIDTH/2 , 284 * 2 };

	UIButton* map_arrow_right = nullptr;
	Rectangle map_arrow_right_rec = { (462 * 2), (190 * 2), 15 * 2, 13 * 2 };
	UIButton* map_arrow_left = nullptr;
	Rectangle map_arrow_left_rec = { (167 * 2), (190 * 2), 15 * 2, 13 * 2 };

	Animator* arrowRightSetupMapAnimator = nullptr;
	Animator* arrowLeftSetupMapAnimator = nullptr;

	bool justClickedarrowRightSetupMap = false;
	bool justClickedarrowLeftSetupMap = false;

	bool isMapChosen = false;
};