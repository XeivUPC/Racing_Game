#pragma once

#include "ModuleScene.h"

#include "UIElement.h"
#include "UIButton.h"
#include "UISlider.h"

class Application;


class SceneOptions : public ModuleScene {
private: 

	bool enabled;

	int currentLanguage = 0;
	
	UIButton* exitSettingsButton = nullptr;
	UIButton* nextLanguageButton = nullptr;
	UIButton* previousLanguageButton = nullptr;

	UISlider* generalVolumeSlider = nullptr;
	UISlider* musicVolumeSlider = nullptr;
	UISlider* sfxVolumeSlider = nullptr;

	Vector2 generalVolumeSliderSize = { 0,0 };
	Vector2 musicVolumeSliderSize = { 0,0 };
	Vector2 sfxVolumeSliderSize = { 0,0 };

	int audioId = -1;

public:

	SceneOptions(Application* app, bool start_enabled = false);

	// Destructor
	virtual ~SceneOptions();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void Exit();
	void NextLanguage();
	void PreviousLanguage();
	void OnMouseOverExit();
};