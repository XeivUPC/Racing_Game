#pragma once

#include "ModuleScene.h"

#include "UIElement.h"
#include "UIButton.h"
#include "UISlider.h"

class Application;

enum Language {
	ENGLISH,
	SPANISH,
	CATALAN
};

class SceneOptions : public ModuleScene {
private: 

	bool enabled;

	Vector2 sliderVolumePosition = {0,0};
	
	UIButton* exitSettingsButton = nullptr;
	UIButton* nextLanguageButton = nullptr;
	UIButton* previousLanguageButton = nullptr;

	UISlider* generalVolumeSlider = nullptr;
	UISlider* musicVolumeSlider = nullptr;
	UISlider* sfxVolumeSlider = nullptr;

public:

	SceneOptions(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~SceneOptions();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};