#include "Globals.h"
#include "Application.h"
#include "SceneOptions.h"

SceneOptions::SceneOptions(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{
	
}

// Destructor
SceneOptions::~SceneOptions()
{
}

bool SceneOptions::Init()
{
	LOG("Init options");
	bool ret = true;

	/* Create UI */

	//Create Buttons
	float exitSettingsButtonOffset = 30;
	Vector2 exitSettingsButtonSize = { 30,30 };
	exitSettingsButton = new UIButton(this, Vector2{ SCREEN_WIDTH - (exitSettingsButtonSize.x / 2) - exitSettingsButtonOffset, SCREEN_HEIGHT + exitSettingsButtonOffset}, exitSettingsButtonSize);

	float languageButtonOffsetY = 0;
	float offsetBetweenTextAndButtonLanguage = 30;
	Vector2 languageButtonSize = { 30,30 };
	nextLanguageButton = new UIButton(this, Vector2{ SCREEN_WIDTH / 2 - (languageButtonSize.x) /*- LanguageTextSize/2*/ - offsetBetweenTextAndButtonLanguage, (SCREEN_HEIGHT / 6) * 2 + languageButtonOffsetY }, languageButtonSize);
	previousLanguageButton = new UIButton(this, Vector2{ SCREEN_WIDTH / 2 + (languageButtonSize.x) /*+ LanguageTextSize/2*/ + offsetBetweenTextAndButtonLanguage, (SCREEN_HEIGHT / 6) * 2 + languageButtonOffsetY }, languageButtonSize);

	//Create Sliders
	float generalVolumeSliderOffsetY = 0;
	Vector2 generalVolumeSliderSize = { 50,10 };
	generalVolumeSlider = new UISlider(this, Vector2{ SCREEN_WIDTH / 2 - (generalVolumeSliderSize.x) , (SCREEN_HEIGHT / 6) * 4 + generalVolumeSliderOffsetY }, generalVolumeSliderSize);

	float musicVolumeSliderOffsetY = 0;
	Vector2 musicVolumeSliderSize = { 50,10 };
	musicVolumeSlider = new UISlider(this, Vector2{ SCREEN_WIDTH / 2 - (musicVolumeSliderSize.x) , (SCREEN_HEIGHT / 6) * 5 + musicVolumeSliderOffsetY }, musicVolumeSliderSize);

	float sfxVolumeSliderOffsetY = 0;
	Vector2 sfxVolumeSliderSize = { 50,10 };
	sfxVolumeSlider = new UISlider(this, Vector2{ SCREEN_WIDTH / 2 - (sfxVolumeSliderSize.x) , (SCREEN_HEIGHT / 6) * 6 + sfxVolumeSliderOffsetY }, sfxVolumeSliderSize);

	return ret;
}

update_status SceneOptions::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status SceneOptions::Update()
{
	return UPDATE_CONTINUE;
}

update_status SceneOptions::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool SceneOptions::CleanUp()
{
	LOG("Close Options");

	return true;
}
