//#pragma once
//
//#include "Globals.h"
//#include "ModuleScene.h"
//
//#include "p2Point.h"
//
//#include "raylib.h"
//#include <vector>
//
//class UIElement;
//class UIButton;
//class UISlider;
//
//class SceneOptions : public ModuleScene {
//private: 
//	
//	UIButton* exitSettingsButton = nullptr;
//	UIButton* nextLanguageButton = nullptr;
//	UIButton* previousLanguageButton = nullptr;
//
//	UISlider* generalVolumeSlider = nullptr;
//	UISlider* musicVolumeSlider = nullptr;
//	UISlider* sfxVolumeSlider = nullptr;
//
//	Vector2 generalVolumeSliderSize = { 0,0 };
//	Vector2 musicVolumeSliderSize = { 0,0 };
//	Vector2 sfxVolumeSliderSize = { 0,0 };
//
//	int audioId = -1;
//
//	Texture2D* backgroundTextureSettings = nullptr;
//	Rectangle  backgroundTextureRec = { 0, 0, 640, 360 };
//
//	int languageIndex = 0;
//
//public:
//
//	SceneOptions(Application* app, bool start_enabled = false);
//
//	// Destructor
//	~SceneOptions();
//
//	bool Start();
//	update_status Update();
//	bool CleanUp();
//
//	void Exit();
//	void NextLanguage();
//	void PreviousLanguage();
//};