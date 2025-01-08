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
		Rectangle fixedRectangle;
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
	string vehicleType ="";
	int maxCharacters = 11;
	int currentVehicle= 0;
	int currentCharacter = 0;
	bool sameVehicle = false;
	Color vehicleColor = WHITE;
	string configPath = "Assets/Data/vehicle_data.xml";

	UIButton* previousVehicle = nullptr;
	void OnMouseClickPreviousVehicle();

	UIButton* nextVehicle = nullptr;
	void OnMouseClickNextVehicle();
	UIButton* previousCharacter = nullptr;
	void OnMouseClickPreviousCharacter();
	UIButton* nextCharacter = nullptr;
	void OnMouseClickNextCharacter();
	UIButton* finish = nullptr;
	void OnMouseClickFinish();
	void DrawSelectionBtnTexture(UIButton* btn);


	vector<Color> availableColors = {WHITE, DARKGRAY, RED, BLUE, YELLOW, GREEN,SKYBLUE, MAGENTA, ORANGE };
	vector<UIButton*> colorBtns;
	Vector2 colorBtnSize = {39,39 };
	Vector2 colorBtnAnchor = { 76,271 };
	void ChangeVehicleColor(Color colorBtn);

};