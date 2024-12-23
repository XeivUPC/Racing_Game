#include "Globals.h"
#include "Application.h"
#include "SceneOptions.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleTexture.h"
#include "ModulePhysics.h"
#include "ModuleAssetLoader.h"
#include "SceneMainMenu.h"
#include "SceneGame.h"

SceneOptions::SceneOptions(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{
	audioId = App->audio->LoadFx("Assets/Sounds/Music/PianoMusic.wav");
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
	exitSettingsButton = new UIButton(this, Vector2{ SCREEN_WIDTH - (exitSettingsButtonSize.x) - exitSettingsButtonOffset, exitSettingsButtonOffset}, exitSettingsButtonSize, WHITE);
	exitSettingsButton->onMouseClick = [&]() {Exit(); };
	exitSettingsButton->onMouseOver = [&]() {OnMouseOverExit(); };

	float languageButtonOffsetY = -70;
	float offsetBetweenTextAndButtonLanguage = 30;
	float LanguageTextSize = 300;
	Vector2 languageButtonSize = { 30,30 };
	nextLanguageButton = new UIButton(this, Vector2{ SCREEN_WIDTH / 2 - (languageButtonSize.x) - (LanguageTextSize/2) - offsetBetweenTextAndButtonLanguage, (SCREEN_HEIGHT / 6) * 2 + languageButtonOffsetY }, languageButtonSize, WHITE);
	previousLanguageButton = new UIButton(this, Vector2{ SCREEN_WIDTH / 2  + (LanguageTextSize/2) + offsetBetweenTextAndButtonLanguage, (SCREEN_HEIGHT / 6) * 2 + languageButtonOffsetY }, languageButtonSize,WHITE);
	nextLanguageButton->onMouseClick = [&]() {Exit(); };
	previousLanguageButton->onMouseClick = [&]() {PreviousLanguage(); };
	nextLanguageButton->onMouseClick = [&]() {NextLanguage(); };

	//Create Sliders
	
	float generalVolumeSliderOffsetY = -100;
	generalVolumeSliderSize = { 300,10 };
	generalVolumeSlider = new UISlider(this, Vector2{ SCREEN_WIDTH / 2 - (generalVolumeSliderSize.x / 2) , (SCREEN_HEIGHT / 6) * 4 + generalVolumeSliderOffsetY }, generalVolumeSliderSize);
	generalVolumeSlider->onMouseClick = [&]() {App->audio->ChangeGeneralVolume(generalVolumeSlider->GetValue()); };

	float musicVolumeSliderOffsetY = -100;
	musicVolumeSliderSize = { 300,10 };
	musicVolumeSlider = new UISlider(this, Vector2{ SCREEN_WIDTH / 2 - (musicVolumeSliderSize.x / 2) , (SCREEN_HEIGHT / 6) * 5 + musicVolumeSliderOffsetY }, musicVolumeSliderSize);
	musicVolumeSlider->onMouseClick = [&]() {App->audio->ChangeMusicVolume(musicVolumeSlider->GetValue()); };

	float sfxVolumeSliderOffsetY = -100;
	sfxVolumeSliderSize = { 300,10 };
	sfxVolumeSlider = new UISlider(this, Vector2{ SCREEN_WIDTH / 2 - (sfxVolumeSliderSize.x / 2) , (SCREEN_HEIGHT / 6) * 6 + sfxVolumeSliderOffsetY }, sfxVolumeSliderSize);
	sfxVolumeSlider->onMouseClick = [&]() {App->audio->ChangeSfxVolume(sfxVolumeSlider->GetValue()); };
	
	App->audio->PlayFx(audioId);
	return ret;
}

update_status SceneOptions::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status SceneOptions::Update()
{
	exitSettingsButton->Update();
	nextLanguageButton->Update();
	previousLanguageButton->Update();
	generalVolumeSlider->Update();
	musicVolumeSlider->Update();
	sfxVolumeSlider->Update();

	exitSettingsButton->Render();
	nextLanguageButton->Render();
	previousLanguageButton->Render();
	generalVolumeSlider->Render();
	musicVolumeSlider->Render();
	sfxVolumeSlider->Render();

	//Draw Text
	float languageTextSize = 200;
	DrawTextEx(App->assetLoader->basicFont, "Language", Vector2{ SCREEN_WIDTH / 2 - languageTextSize / 2 - 50, (SCREEN_HEIGHT / 6) - (SCREEN_HEIGHT / 10) }, 100, 1, BLACK);

	float soundTextSize = 100;
	DrawTextEx(App->assetLoader->basicFont, "Sound", Vector2{ SCREEN_WIDTH / 2 - soundTextSize / 2 - 50, (SCREEN_HEIGHT / 6) * 2 }, 100, 1, BLACK);

	DrawTextEx(App->assetLoader->basicFont, "General", Vector2{ SCREEN_WIDTH / 2 - (generalVolumeSliderSize.x) - 50 , (SCREEN_HEIGHT / 6) * 3 }, 50, 1, BLACK);

	DrawTextEx(App->assetLoader->basicFont, "Music", Vector2{ SCREEN_WIDTH / 2 - (musicVolumeSliderSize.x) - 50 , (SCREEN_HEIGHT / 6) * 4 }, 50, 1, BLACK);

	DrawTextEx(App->assetLoader->basicFont, "SFX", Vector2{ SCREEN_WIDTH / 2 - (musicVolumeSliderSize.x) - 50 , (SCREEN_HEIGHT / 6) * 5 }, 50, 1, BLACK);

	switch (currentLanguage)
	{
		case 0:
			DrawTextEx(App->assetLoader->basicFont, "English", Vector2{ SCREEN_WIDTH / 2 - 70, (SCREEN_HEIGHT / 6) * 2 - 80 }, 50, 1, BLACK);
			break;
		case 1:
			DrawTextEx(App->assetLoader->basicFont, "Castellano", Vector2{ SCREEN_WIDTH / 2 - 100, (SCREEN_HEIGHT / 6) * 2 - 80 }, 50, 1, BLACK);
			break;
		case 2:
			DrawTextEx(App->assetLoader->basicFont, "Catala", Vector2{ SCREEN_WIDTH / 2 - 60, (SCREEN_HEIGHT / 6) * 2 - 80 }, 50, 1, BLACK);
			break;
		default:
			break;
	}
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
	this->StartFadeIn(App->scene_main_menu, BLACK, 1);
}

void SceneOptions::NextLanguage()
{
	if (currentLanguage == 2)
	{
		currentLanguage = 0;
	}
	else
	{
		currentLanguage++;
	}
}

void SceneOptions::PreviousLanguage()
{
	if (currentLanguage == 0)
	{
		currentLanguage = 2;
	}
	else
	{
		currentLanguage--;
	}
}
void SceneOptions::OnMouseOverExit() {
	ModuleRender::RenderLayer last_layer = App->renderer->GetCurrentRenderLayer();
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_5);

	DrawRectangle(SCREEN_WIDTH - 30 - 30, 60, 30, 30, BLACK);

	App->renderer->SelectRenderLayer(last_layer);
}