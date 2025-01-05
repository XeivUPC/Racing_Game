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
	vector<VehicleData> vehicleNames;
	Texture* setup = nullptr;
	Texture* vehicles = nullptr;
	Texture* characters = nullptr;
	Rectangle characterRect = { 0,0,48,48 };
	string vehicleType;
	int maxCharacters = 2;
	int currentVehicle;
	int currentCharacter;
	bool sameVehicle;
	Color color = WHITE;
	string configPath = "Assets/Data/vehicle_data.xml";

	UIButton* previousVehicle;
	void OnMouseClickPreviousVehicle();
	void OnMouseOverPreviousVehicle();
	void OnMouseExitPreviousVehicle();
	UIButton* nextVehicle;
	void OnMouseClickNextVehicle();
	void OnMouseOverNextVehicle();
	void OnMouseExitNextVehicle();
	UIButton* previousCharacter;
	void OnMouseClickPreviousCharacter();
	void OnMouseOverPreviousCharacter();
	void OnMouseExitPreviousCharacter();
	UIButton* nextCharacter;
	void OnMouseClickNextCharacter();
	void OnMouseOverNextCharacter();
	void OnMouseExitNextCharacter();
	UIButton* finish;
	void OnMouseClickFinish();
	void OnMouseOverFinish();
	void OnMouseExitFinish();
};