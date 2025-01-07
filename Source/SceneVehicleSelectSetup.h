#pragma once
#include "ModuleScene.h"
#include <vector>
#include <string>

class Vehicle;
class UIButton;

using namespace std;

class SceneVehicleSelectSetup : public ModuleScene
{
public:
	struct VehicleData
	{
		string id;
		string name;
		Rectangle rectangle;
	};
	SceneVehicleSelectSetup(Application* app, bool start_enabled = false);
	~SceneVehicleSelectSetup();

	bool Start();
	update_status Update();
	bool Render();
	bool CleanUp();
	void LoadVehicles();
	void SetData(string prefix);

private:

	Texture* selectionSlots_texture = nullptr;
	Texture* bg_texture = nullptr;

	Texture* btn_texture = nullptr;
	Rectangle btn_rect = { 0,0,304,71 };
	Rectangle btn_rect_hover = { 305,0,305,71 };
	Rectangle btn_rect_pressed = { 305 * 2,0,305,71 };
	Rectangle btn_rect_locked = { 305 * 3,0,305,71 };


	vector<VehicleData> vehicleNames;
	Texture* vehicles = nullptr;
	Texture* characters = nullptr;
	Rectangle characterRect = { 0,0,48,48 };
	string vehicleType;
	int maxCharacters = 3;
	int currentVehicle;
	int currentCharacter;
	bool sameVehicle;
	Color color = WHITE;
	string configPath = "Assets/Data/vehicle_data.xml";

	UIButton* previousVehicle;
	void OnMouseClickPreviousVehicle();

	UIButton* nextVehicle;
	void OnMouseClickNextVehicle();
	UIButton* previousCharacter;
	void OnMouseClickPreviousCharacter();
	UIButton* nextCharacter;
	void OnMouseClickNextCharacter();
	UIButton* finish;
	void OnMouseClickFinish();

	void DrawSelectionBtnTexture(UIButton* btn);
};