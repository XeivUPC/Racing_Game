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

	App->texture->CreateTexture("Assets/Textures/settings_menu.png", "backgroundSettings");
	backgroundTextureSettings = App->texture->GetTexture("backgroundSettings");

	/* Create UI */

	//Create Buttons
	float exitSettingsButtonOffset = 30;
	Vector2 exitSettingsButtonSize = { 50,50 };
	exitSettingsButton = new UIButton(this, Vector2{ SCREEN_WIDTH - (exitSettingsButtonSize.x) - exitSettingsButtonOffset, exitSettingsButtonOffset}, exitSettingsButtonSize);
	exitSettingsButton->onMouseClick.emplace_back([&]() {Exit(); });

	float languageButtonOffsetY = -70;
	float offsetBetweenTextAndButtonLanguage = 30;
	float LanguageTextSize = 300;
	Vector2 languageButtonSize = { 50,50 };
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
	delete exitSettingsButton;
	delete nextLanguageButton;
	delete previousLanguageButton;
	
	delete generalVolumeSlider;
	delete musicVolumeSlider;
	delete sfxVolumeSlider;

	return true;
}

void SceneOptions::Exit()
{
	//Go to MainMenu or the Game Scene
	StartFadeIn(App->scene_main_menu, BLACK, 1);
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

	Vector2 textSize_language = MeasureTextEx(App->assetLoader->titleFont, App->localization->GetString("SETTINGS_LANGUAGE").c_str(), 100, 0);
	App->renderer->DrawText(App->localization->GetString("SETTINGS_LANGUAGE").c_str(), Vector2{ (SCREEN_WIDTH / 2) - (textSize_language.x / 2), (SCREEN_HEIGHT / 6) - (SCREEN_HEIGHT / 10) }, Vector2{ 0,0 }, App->assetLoader->titleFont, 100, 1, WHITE);

	Vector2 textSize_language_select = MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("Language").c_str(), 60, 0);
	App->renderer->DrawText(App->localization->GetString("Language").c_str(), Vector2{ (SCREEN_WIDTH / 2) - (textSize_language_select.x / 2) , (SCREEN_HEIGHT / 6) * 2 - 70 }, Vector2{ 0,0 }, App->assetLoader->agencyB, 60, 1, BLACK);

	Vector2 textSize_sound = MeasureTextEx(App->assetLoader->titleFont, App->localization->GetString("SETTINGS_SOUND").c_str(), 100, 0);
	App->renderer->DrawText(App->localization->GetString("SETTINGS_SOUND").c_str(),Vector2{ (SCREEN_WIDTH / 2) - (textSize_sound.x / 2), (SCREEN_HEIGHT / 6) * 2 }, Vector2{0,0}, App->assetLoader->titleFont, 100, 1, WHITE);

	Vector2 textSize_general = MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("SETTINGS_GENERAL").c_str(), 60, 0);
	App->renderer->DrawText(App->localization->GetString("SETTINGS_GENERAL").c_str(), Vector2{ (SCREEN_WIDTH / 2) - (textSize_general.x) - (generalVolumeSliderSize.x /2), (SCREEN_HEIGHT / 6) * 3.15f }, Vector2{ 0,0 }, App->assetLoader->agencyB, 60, 1, RED);

	Vector2 textSize_music = MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("SETTINGS_MUSIC").c_str(), 60, 0);
	App->renderer->DrawText(App->localization->GetString("SETTINGS_MUSIC").c_str(), Vector2{ (SCREEN_WIDTH / 2) - (textSize_music.x) - (musicVolumeSliderSize.x / 2), (SCREEN_HEIGHT / 6) * 4.15f }, Vector2{ 0,0 }, App->assetLoader->agencyB, 60, 1, RED);

	Vector2 textSize_sfx = MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("SETTINGS_SFX").c_str(), 60, 0);
	App->renderer->DrawText(App->localization->GetString("SETTINGS_SFX").c_str(), Vector2{ (SCREEN_WIDTH / 2) - (textSize_sfx.x) - (sfxVolumeSliderSize.x / 2), (SCREEN_HEIGHT / 6) * 5.15f }, Vector2{ 0,0 }, App->assetLoader->agencyB, 60, 1, RED);

	App->renderer->UnlockRenderLayer();

	FadeRender();

	return true;
}
