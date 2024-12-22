#include "Globals.h"
#include "Application.h"
#include "SceneOptions.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleTexture.h"
#include "ModulePhysics.h"
#include "ModuleAssetLoader.h"

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

	ModuleRender::RenderLayer last_layer = App->renderer->GetCurrentRenderLayer();
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_5);
	App->renderer->SelectRenderLayer(last_layer);

	/* Create UI */

	//Create Buttons
	//App->renderer->DrawText("Language", Vector2{ SCREEN_WIDTH / 2 - soundTextSize / 2, (SCREEN_HEIGHT / 6) }, Vector2{-50,0}, App->assetLoader->basicFont, 1, BLACK);

	float exitSettingsButtonOffset = 30;
	Vector2 exitSettingsButtonSize = { 30,30 };
	exitSettingsButton = new UIButton(this, Vector2{ SCREEN_WIDTH - (exitSettingsButtonSize.x) - exitSettingsButtonOffset, exitSettingsButtonOffset}, exitSettingsButtonSize, WHITE);
	exitSettingsButton->onMouseClick = [&]() {Exit(); };

	float languageButtonOffsetY = -50;
	float offsetBetweenTextAndButtonLanguage = 30;
	float LanguageTextSize = 300;
	Vector2 languageButtonSize = { 30,30 };
	nextLanguageButton = new UIButton(this, Vector2{ SCREEN_WIDTH / 2 - (languageButtonSize.x) - (LanguageTextSize/2) - offsetBetweenTextAndButtonLanguage, (SCREEN_HEIGHT / 6) * 2 + languageButtonOffsetY }, languageButtonSize, WHITE);
	previousLanguageButton = new UIButton(this, Vector2{ SCREEN_WIDTH / 2  + (LanguageTextSize/2) + offsetBetweenTextAndButtonLanguage, (SCREEN_HEIGHT / 6) * 2 + languageButtonOffsetY }, languageButtonSize,WHITE);
	nextLanguageButton->onMouseClick = [&]() {Exit(); };
	previousLanguageButton->onMouseClick = [&]() {PreviousLanguage(); };
	nextLanguageButton->onMouseClick = [&]() {NextLanguage(); };

	//Create Sliders
	float soundTextSize = 100;
	//App->renderer->DrawText("Sound", Vector2{ SCREEN_WIDTH / 2 - soundTextSize / 2, (SCREEN_HEIGHT / 6) * 3 }, Vector2{-50,0}, App->assetLoader->basicFont, 1, BLACK);

	float generalVolumeSliderOffsetY = -100;
	Vector2 generalVolumeSliderSize = { 300,10 };
	generalVolumeSlider = new UISlider(this, Vector2{ SCREEN_WIDTH / 2 - (generalVolumeSliderSize.x / 2) , (SCREEN_HEIGHT / 6) * 4 + generalVolumeSliderOffsetY }, generalVolumeSliderSize);
	//App->renderer->DrawText("General", Vector2{ SCREEN_WIDTH / 2 - (generalVolumeSliderSize.x) , (SCREEN_HEIGHT / 6) * 4 }, Vector2{-50,0}, App->assetLoader->basicFont, 1, BLACK);

	float musicVolumeSliderOffsetY = -100;
	Vector2 musicVolumeSliderSize = { 300,10 };
	musicVolumeSlider = new UISlider(this, Vector2{ SCREEN_WIDTH / 2 - (musicVolumeSliderSize.x / 2) , (SCREEN_HEIGHT / 6) * 5 + musicVolumeSliderOffsetY }, musicVolumeSliderSize);
	//App->renderer->DrawText("Music", Vector2{ SCREEN_WIDTH / 2 - (musicVolumeSliderSize.x) , (SCREEN_HEIGHT / 6) * 5 + musicVolumeSliderOffsetY }, Vector2{ -50,0 }, App->assetLoader->basicFont, 1, BLACK);

	float sfxVolumeSliderOffsetY = -100;
	Vector2 sfxVolumeSliderSize = { 300,10 };
	sfxVolumeSlider = new UISlider(this, Vector2{ SCREEN_WIDTH / 2 - (sfxVolumeSliderSize.x / 2) , (SCREEN_HEIGHT / 6) * 6 + sfxVolumeSliderOffsetY }, sfxVolumeSliderSize);
	//App->renderer->DrawText("SFX", Vector2{ SCREEN_WIDTH / 2 - (sfxVolumeSliderSize.x) , (SCREEN_HEIGHT / 6) * 6 + sfxVolumeSliderOffsetY }, Vector2{ -50,0 }, App->assetLoader->basicFont, 1, BLACK);

	
	return ret;
}

update_status SceneOptions::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status SceneOptions::Update()
{
	exitSettingsButton->Render();
	nextLanguageButton->Render();
	previousLanguageButton->Render();
	generalVolumeSlider->Render();
	musicVolumeSlider->Render();
	sfxVolumeSlider->Render();

	return UPDATE_CONTINUE;
}

update_status SceneOptions::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool SceneOptions::CleanUp()
{
	LOG("Close Options");

	//Fix memory leaks
	return true;
}

void SceneOptions::Exit()
{
	//Go to MainMenu or the Game Scene
}

void SceneOptions::NextLanguage()
{
	if (currentLanguage == 3)
	{
		currentLanguage = 0;
	}
	else
	{
		currentLanguage = currentLanguage + 1;
	}
}

void SceneOptions::PreviousLanguage()
{
	if (currentLanguage == 0)
	{
		currentLanguage = 3;
	}
	else
	{
		currentLanguage = currentLanguage - 1;
	}
}
