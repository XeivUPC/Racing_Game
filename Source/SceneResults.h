#pragma once

#include "ModuleScene.h"
#include <vector>

class UIButton;
class Pilot;

class SceneResults : public ModuleScene
{
public:
	SceneResults(Application* app, bool start_enabled = true);
	~SceneResults();

	bool Start();
	update_status Update();
	bool Render();
	bool CleanUp();

	struct PilotDataResults {
		std::string name;
		int characterIndex;
		bool isPlayer = false;
	};

private:

	void ClickNext();
	void OnMouseOverNext();

	Texture2D* backgroundTexture = nullptr;
	Rectangle  backgroundTextureRec = { 0, 0, 1280, 720 };

	UIButton* next_button = nullptr;
	Texture2D* next_buttonTexture_hover = nullptr;
	Rectangle  next_buttonTextureRec = { (47 * 8), (72 * 8), 528, 96 };
	Rectangle  next_button_section = { 0, 0, 528, 96 };

	Vector2 buttonsText_Offset = { 0, 8 };

	Vector2 pilotsPos = { SCREEN_WIDTH / 2, 80 };
	std::vector<PilotDataResults> pilotDatas;

	double bestLapTime = -1;
};
