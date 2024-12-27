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
#include "UIElement.h"
#include "UIButton.h"
#include "UISlider.h"
#include "ModuleLocalization.h"

SceneOptions::SceneOptions(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{
	
}

// Destructor
SceneOptions::~SceneOptions()
{
}

bool SceneOptions::Start()
{
	LOG("Init options");
	bool ret = true;

	/* Create Audio */
	audioId = App->audio->LoadFx("Assets/Sounds/Music/PianoMusic.wav");

	/* Create Textures */

	App->texture->CreateTexture("Assets/Textures/main_menu.png", "backgroundSettings");
	backgroundTextureSettings = App->texture->GetTexture("backgroundSettings");

	/* Create UI */

	//Create Buttons
	float exitSettingsButtonOffset = 30;
	Vector2 exitSettingsButtonSize = { 30,30 };
	exitSettingsButton = new UIButton(this, Vector2{ SCREEN_WIDTH - (exitSettingsButtonSize.x) - exitSettingsButtonOffset, exitSettingsButtonOffset}, exitSettingsButtonSize);
	exitSettingsButton->onMouseClick.emplace_back([&]() {Exit(); });

	float languageButtonOffsetY = -70;
	float offsetBetweenTextAndButtonLanguage = 30;
	float LanguageTextSize = 300;
	Vector2 languageButtonSize = { 30,30 };
	nextLanguageButton = new UIButton(this, Vector2{ SCREEN_WIDTH / 2 - (languageButtonSize.x) - (LanguageTextSize/2) - offsetBetweenTextAndButtonLanguage, (SCREEN_HEIGHT / 6) * 2 + languageButtonOffsetY }, languageButtonSize);
	previousLanguageButton = new UIButton(this, Vector2{ SCREEN_WIDTH / 2  + (LanguageTextSize/2) + offsetBetweenTextAndButtonLanguage, (SCREEN_HEIGHT / 6) * 2 + languageButtonOffsetY }, languageButtonSize);
	previousLanguageButton->onMouseClick.emplace_back([&]() {PreviousLanguage(); });
	nextLanguageButton->onMouseClick.emplace_back([&]() {NextLanguage(); });

	//Create Sliders
	
	float generalVolumeSliderOffsetY = -100;
	generalVolumeSliderSize = { 300,10 };
	generalVolumeSlider = new UISlider(this, Vector2{ SCREEN_WIDTH / 2 - (generalVolumeSliderSize.x / 2) , (SCREEN_HEIGHT / 6) * 4 + generalVolumeSliderOffsetY }, generalVolumeSliderSize);
	generalVolumeSlider->onMouseClick.emplace_back([&]() {App->audio->ChangeGeneralVolume(generalVolumeSlider->GetValue()); });

	float musicVolumeSliderOffsetY = -100;
	musicVolumeSliderSize = { 300,10 };
	musicVolumeSlider = new UISlider(this, Vector2{ SCREEN_WIDTH / 2 - (musicVolumeSliderSize.x / 2) , (SCREEN_HEIGHT / 6) * 5 + musicVolumeSliderOffsetY }, musicVolumeSliderSize);
	musicVolumeSlider->onMouseClick.emplace_back([&]() {App->audio->ChangeMusicVolume(musicVolumeSlider->GetValue()); });

	float sfxVolumeSliderOffsetY = -100;
	sfxVolumeSliderSize = { 300,10 };
	sfxVolumeSlider = new UISlider(this, Vector2{ SCREEN_WIDTH / 2 - (sfxVolumeSliderSize.x / 2) , (SCREEN_HEIGHT / 6) * 6 + sfxVolumeSliderOffsetY }, sfxVolumeSliderSize);
	sfxVolumeSlider->onMouseClick.emplace_back([&]() {App->audio->ChangeSfxVolume(sfxVolumeSlider->GetValue()); });
	
	App->audio->PlayFx(audioId);
	return ret;
}

update_status SceneOptions::Update()
{
	exitSettingsButton->Update();
	nextLanguageButton->Update();
	previousLanguageButton->Update();
	generalVolumeSlider->Update();
	musicVolumeSlider->Update();
	sfxVolumeSlider->Update();

	
	FadeUpdate();

	Render();

	return UPDATE_CONTINUE;
}

bool SceneOptions::CleanUp()
{
	LOG("Close Options");

	//Fix memory leaks
	/*delete exitSettingsButton;
	delete nextLanguageButton;
	delete previousLanguageButton;
	
	delete generalVolumeSlider;
	delete musicVolumeSlider;
	delete sfxVolumeSlider;*/

	return true;
}

void SceneOptions::Exit()
{
	//Go to MainMenu or the Game Scene
	/*this->StartFadeIn(App->scene_main_menu, BLACK, 0.3f);*/
}

void SceneOptions::NextLanguage()
{
	languageIndex++;
	if (languageIndex > 2)
	{
		languageIndex = 0;
	}

	App->localization->ChangeLanguage((Language)languageIndex);

}

void SceneOptions::PreviousLanguage()
{
	languageIndex--;
	if (languageIndex < 0)
	{
		languageIndex = 2;
	}

	App->localization->ChangeLanguage((Language)languageIndex);

}
bool SceneOptions::Render() {

	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_3);
	App->renderer->Draw(*backgroundTextureSettings, { backgroundTextureSettingsRec.x, backgroundTextureSettingsRec.y }, { 0,0 }, &backgroundTextureSettingsRec, 0, 2);
	
	//Draw Text
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_5);
	App->renderer->BlockRenderLayer();
	float languageTextSize = 200;
	App->renderer->DrawText(App->localization->GetString("SETTINGS_LANGUAGE").c_str(), Vector2{ SCREEN_WIDTH / 2 - languageTextSize / 2 - 50, (SCREEN_HEIGHT / 6) - (SCREEN_HEIGHT / 10) }, { 0,0 }, App->assetLoader->agencyB, 100, 1, BLACK);

	float soundTextSize = 100;
	DrawTextEx(App->assetLoader->basicFont, App->localization->GetString("SETTINGS_SOUND").c_str(), Vector2{ SCREEN_WIDTH / 2 - soundTextSize / 2 - 50, (SCREEN_HEIGHT / 6) * 2 }, 100, 1, BLACK);

	DrawTextEx(App->assetLoader->basicFont, App->localization->GetString("SETTINGS_GENERAL").c_str(), Vector2{ SCREEN_WIDTH / 2 - (generalVolumeSliderSize.x) - 50 , (SCREEN_HEIGHT / 6) * 3 }, 50, 1, BLACK);

	DrawTextEx(App->assetLoader->basicFont, App->localization->GetString("SETTINGS_MUSIC").c_str(), Vector2{ SCREEN_WIDTH / 2 - (musicVolumeSliderSize.x) - 50 , (SCREEN_HEIGHT / 6) * 4 }, 50, 1, BLACK);

	DrawTextEx(App->assetLoader->basicFont, App->localization->GetString("SETTINGS_SFX").c_str(), Vector2{ SCREEN_WIDTH / 2 - (musicVolumeSliderSize.x) - 50 , (SCREEN_HEIGHT / 6) * 5 }, 50, 1, BLACK);

	DrawTextEx(App->assetLoader->basicFont, App->localization->GetString("Language").c_str(), Vector2{ SCREEN_WIDTH / 2 - 70, (SCREEN_HEIGHT / 6) * 2 - 80 }, 50, 1, BLACK);
	App->renderer->UnlockRenderLayer();

	/*App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_3);
	App->renderer->Draw(*backgroundTexture, { backgroundTextureRec.x, backgroundTextureRec.y }, { 0,0 }, &backgroundTextureRec, 0, 2);

	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_4);
	if (App->localization->GetString("MAINMENU_PLAY").length() < 5) {
		App->renderer->DrawText(App->localization->GetString("MAINMENU_PLAY").c_str(), { play_buttonTextureRec.x , play_buttonTextureRec.y }, { buttonsText_Offset.x + App->assetLoader->titleFont.recs->width, buttonsText_Offset.y }, App->assetLoader->titleFont, 100, 0, WHITE);
	}
	else {
		App->renderer->DrawText(App->localization->GetString("MAINMENU_PLAY").c_str(), { play_buttonTextureRec.x , play_buttonTextureRec.y }, buttonsText_Offset, App->assetLoader->titleFont, 100, 0, WHITE);
	}

	App->renderer->DrawText(App->localization->GetString("MAINMENU_SETTINGS").c_str(), { settings_buttonTextureRec.x , settings_buttonTextureRec.y }, buttonsText_Offset, App->assetLoader->titleFont, 100, 0, WHITE);

	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_5);
	FadeUpdate();*/

	FadeRender();

	return true;
}
