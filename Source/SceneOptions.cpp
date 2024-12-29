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
#include "AnimationSystem.h"
#include "Timer.h"

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

	/* Get Textures */

	backgroundTextureSettings = App->texture->GetTexture("backgroundSettings");
	thumbTextureSettings = App->texture->GetTexture("sliderThumbSettings");
	arrowLanguageSettings = App->texture->GetTexture("arrowSettings");

	/* Create Animations */

	//Button Next Language
	arrowRightSettingsLanguageAnimator = new Animator(App);

	AnimationData arrowRightLanguageIdleAnim = AnimationData("arrowRightLanguageIdle");
	arrowRightLanguageIdleAnim.AddSprite(Sprite{ arrowLanguageSettings,{0, 0}, {48,48} });

	AnimationData arrowRightLanguageOverAnim = AnimationData("arrowRightLanguageOver");
	arrowRightLanguageOverAnim.AddSprite(Sprite{ arrowLanguageSettings,{1, 0}, {48,48} });

	AnimationData arrowRightLanguageClickAnim = AnimationData("arrowRightLanguageClick");
	arrowRightLanguageClickAnim.AddSprite(Sprite{ arrowLanguageSettings,{2, 0}, {48,48} });

	arrowRightSettingsLanguageAnimator->AddAnimation(arrowRightLanguageIdleAnim);
	arrowRightSettingsLanguageAnimator->AddAnimation(arrowRightLanguageOverAnim);
	arrowRightSettingsLanguageAnimator->AddAnimation(arrowRightLanguageClickAnim);
	arrowRightSettingsLanguageAnimator->SetSpeed(1.f);
	arrowRightSettingsLanguageAnimator->SelectAnimation("arrowRightLanguageIdle", true);

	//Button Previous Language
	arrowLeftSettingsLanguageAnimator = new Animator(App);

	AnimationData arrowLeftLanguageIdleAnim = AnimationData("arrowLeftLanguageIdle");
	arrowLeftLanguageIdleAnim.AddSprite(Sprite{ arrowLanguageSettings,{0, 0}, {48,48} });

	AnimationData arrowLeftLanguageOverAnim = AnimationData("arrowLeftLanguageOver");
	arrowLeftLanguageOverAnim.AddSprite(Sprite{ arrowLanguageSettings,{1, 0}, {48,48} });

	AnimationData arrowLeftLanguageClickAnim = AnimationData("arrowLeftLanguageClick");
	arrowLeftLanguageClickAnim.AddSprite(Sprite{ arrowLanguageSettings,{2, 0}, {48,48} });

	arrowLeftSettingsLanguageAnimator->AddAnimation(arrowLeftLanguageIdleAnim);
	arrowLeftSettingsLanguageAnimator->AddAnimation(arrowLeftLanguageOverAnim);
	arrowLeftSettingsLanguageAnimator->AddAnimation(arrowLeftLanguageClickAnim);
	arrowLeftSettingsLanguageAnimator->SetSpeed(1.f);
	arrowLeftSettingsLanguageAnimator->SelectAnimation("arrowLeftLanguageIdle", true);

	/* Create UI */

	//_Create Buttons_

	//Button Exit
	float exitSettingsButtonOffset = 30;
	exitSettingsButtonSize = { 48,48 };
	exitSettingsButton = new UIButton(this, Vector2{ SCREEN_WIDTH - (exitSettingsButtonSize.x) - exitSettingsButtonOffset, exitSettingsButtonOffset}, exitSettingsButtonSize);
	exitSettingsButton->onMouseClick.emplace_back([&]() {Exit(); });

	//Buttons Language
	languageButtonSize = { 48,48 };

	nextLanguageButton = new UIButton(this, Vector2{ SCREEN_WIDTH / 2 + 130, (SCREEN_HEIGHT / 6) * 2 - 70}, languageButtonSize);
	nextLanguageButton->onMouseClick.emplace_back([&]() {NextLanguage(); });
	nextLanguageButton->onMouseEnter.emplace_back([&]() {EnterNextLanguage(); });
	nextLanguageButton->onMouseExit.emplace_back([&]() {ExitLanguage(); });

	previousLanguageButton = new UIButton(this, Vector2{ SCREEN_WIDTH / 2 - languageButtonSize.x - 130, (SCREEN_HEIGHT / 6) * 2 - 70 }, languageButtonSize);
	previousLanguageButton->onMouseClick.emplace_back([&]() {PreviousLanguage(); });
	previousLanguageButton->onMouseEnter.emplace_back([&]() {EnterPreviousLanguage(); });
	previousLanguageButton->onMouseExit.emplace_back([&]() {ExitLanguage(); });

	//_Create Sliders_
	
	Vector2 textSize_agencyB = MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("SETTINGS_SFX").c_str(), 60, 0);

	//Slider General Volume
	generalVolumeSliderSize = { 300,10 };
	generalVolumeSlider = new UISlider(this, Vector2{ SCREEN_WIDTH / 2 - (generalVolumeSliderSize.x / 2) , (SCREEN_HEIGHT / 6) * 3.15f + (textSize_agencyB.y / 2) - (generalVolumeSliderSize.y / 2) }, generalVolumeSliderSize, {30,30});

	float general_value = generalVolumeSlider->GetValue();
	generalVolumeSlider->onValueChange.emplace_back([&](float general_value) {App->audio->ChangeGeneralVolume(general_value); });

	generalVolumeSlider->SetValue(0.5f);

	//Slider Music Volume
	musicVolumeSliderSize = { 300,10 };
	musicVolumeSlider = new UISlider(this, Vector2{ SCREEN_WIDTH / 2 - (musicVolumeSliderSize.x / 2) , (SCREEN_HEIGHT / 6) * 4.15f + (textSize_agencyB.y / 2) - (musicVolumeSliderSize.y / 2) }, musicVolumeSliderSize, { 30,30 });

	float music_value = musicVolumeSlider->GetValue();
	musicVolumeSlider->onValueChange.emplace_back([&](float music_value) {App->audio->ChangeMusicVolume(music_value); });

	musicVolumeSlider->SetValue(0.5f);

	//Slider SFX Volume
	sfxVolumeSliderSize = { 300,10 };
	sfxVolumeSlider = new UISlider(this, Vector2{ SCREEN_WIDTH / 2 - (sfxVolumeSliderSize.x / 2) , (SCREEN_HEIGHT / 6) * 5.15f + (textSize_agencyB.y / 2) - (sfxVolumeSliderSize.y / 2) }, sfxVolumeSliderSize, { 30,30 });
	
	float sfx_value = sfxVolumeSlider->GetValue();
	sfxVolumeSlider->onValueChange.emplace_back([&](float sfx_value) {App->audio->ChangeSfxVolume(sfx_value); });

	sfxVolumeSlider->SetValue(0.5f);

	return ret;
}

update_status SceneOptions::Update()
{
	Render();

	exitSettingsButton->Update();
	nextLanguageButton->Update();
	previousLanguageButton->Update();
	generalVolumeSlider->Update();
	musicVolumeSlider->Update();
	sfxVolumeSlider->Update();

	if (ButtonAnimTimer.ReadSec() > ButtonAnimTime && hasClicked)
	{
		arrowLeftSettingsLanguageAnimator->SelectAnimation("arrowLeftLanguageOver", false);
		arrowRightSettingsLanguageAnimator->SelectAnimation("arrowRightLanguageOver", false);
	}

	FadeUpdate();

	return UPDATE_CONTINUE;
}

bool SceneOptions::CleanUp()
{
	LOG("Close Options");

	//Fix memory leaks
	if (arrowRightSettingsLanguageAnimator != nullptr) {
		delete arrowRightSettingsLanguageAnimator;
		arrowRightSettingsLanguageAnimator = nullptr;
	}
	if (arrowLeftSettingsLanguageAnimator != nullptr) {
		delete arrowLeftSettingsLanguageAnimator;
		arrowLeftSettingsLanguageAnimator = nullptr;
	}

	delete exitSettingsButton;
	delete nextLanguageButton;
	delete previousLanguageButton;
	
	delete generalVolumeSlider;
	delete musicVolumeSlider;
	delete sfxVolumeSlider;

	return true;
}

bool SceneOptions::Render() {

	//Draw Background
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
	App->renderer->DrawText(App->localization->GetString("SETTINGS_SOUND").c_str(), Vector2{ (SCREEN_WIDTH / 2) - (textSize_sound.x / 2), (SCREEN_HEIGHT / 6) * 2 }, Vector2{ 0,0 }, App->assetLoader->titleFont, 100, 1, WHITE);

	float OffsetTextToSliderX = 20;

	Vector2 textSize_general = MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("SETTINGS_GENERAL").c_str(), 60, 0);
	App->renderer->DrawText(App->localization->GetString("SETTINGS_GENERAL").c_str(), Vector2{ (SCREEN_WIDTH / 2) - (textSize_general.x) - (generalVolumeSliderSize.x / 2) - OffsetTextToSliderX, (SCREEN_HEIGHT / 6) * 3.15f }, Vector2{ 0,0 }, App->assetLoader->agencyB, 60, 1, BLACK);

	Vector2 textSize_music = MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("SETTINGS_MUSIC").c_str(), 60, 0);
	App->renderer->DrawText(App->localization->GetString("SETTINGS_MUSIC").c_str(), Vector2{ (SCREEN_WIDTH / 2) - (textSize_music.x) - (musicVolumeSliderSize.x / 2) - OffsetTextToSliderX, (SCREEN_HEIGHT / 6) * 4.15f }, Vector2{ 0,0 }, App->assetLoader->agencyB, 60, 1, BLACK);

	Vector2 textSize_sfx = MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("SETTINGS_SFX").c_str(), 60, 0);
	App->renderer->DrawText(App->localization->GetString("SETTINGS_SFX").c_str(), Vector2{ (SCREEN_WIDTH / 2) - (textSize_sfx.x) - (sfxVolumeSliderSize.x / 2) - OffsetTextToSliderX, (SCREEN_HEIGHT / 6) * 5.15f }, Vector2{ 0,0 }, App->assetLoader->agencyB, 60, 1, BLACK);

	App->renderer->UnlockRenderLayer();

	//Draw UI
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_2);
	App->renderer->BlockRenderLayer();

	arrowRightSettingsLanguageAnimator->Animate(Vector2{ SCREEN_WIDTH / 2 + 130, (SCREEN_HEIGHT / 6) * 2 - 70 }, {0,0},0, 1, false);
	arrowRightSettingsLanguageAnimator->Update();

	arrowLeftSettingsLanguageAnimator->Animate(Vector2{ SCREEN_WIDTH / 2 - languageButtonSize.x - 130, (SCREEN_HEIGHT / 6) * 2 - 70 }, {0,0}, 0, 1, false);
	arrowLeftSettingsLanguageAnimator->Update();

	App->renderer->DrawSimpleRectangle(generalVolumeSlider->bounds, Color{ 101, 116, 129, 255 });
	App->renderer->Draw(*thumbTextureSettings, { generalVolumeSlider->GetThumbBounds().x, generalVolumeSlider->GetThumbBounds().y }, { 0,0 }, &thumbTextureSettingsRec, 0, 1);

	App->renderer->DrawSimpleRectangle(musicVolumeSlider->bounds, Color{ 101, 116, 129, 255 });
	App->renderer->Draw(*thumbTextureSettings, { musicVolumeSlider->GetThumbBounds().x, musicVolumeSlider->GetThumbBounds().y }, { 0,0 }, &thumbTextureSettingsRec, 0, 1);

	App->renderer->DrawSimpleRectangle(sfxVolumeSlider->bounds, Color{ 101, 116, 129, 255 });
	App->renderer->Draw(*thumbTextureSettings, { sfxVolumeSlider->GetThumbBounds().x, sfxVolumeSlider->GetThumbBounds().y }, { 0,0 }, &thumbTextureSettingsRec, 0, 1);

	App->renderer->UnlockRenderLayer();

	//Draw Values
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_2);
	App->renderer->BlockRenderLayer();

	//float volumeValue = generalVolumeSlider->GetValue() * 100;
	//std::string volumeValueString = std::to_string(volumeValue);
	//
	//App->renderer->DrawText(volumeValueString, Vector2{(SCREEN_WIDTH / 2) + (sfxVolumeSliderSize.x / 2) + OffsetTextToSliderX, (SCREEN_HEIGHT / 6) * 3.15f }, Vector2{0,0}, App->assetLoader->agencyB, 60, 1, BLACK);

	//const char* musicVolumeValue = musicVolumeSlider->GetValue() * 100;
	//App->renderer->DrawText(musicVolumeValue, Vector2{ (SCREEN_WIDTH / 2)  + (sfxVolumeSliderSize.x / 2) + OffsetTextToSliderX, (SCREEN_HEIGHT / 6) * 4.15f }, Vector2{ 0,0 }, App->assetLoader->agencyB, 60, 1, BLACK);

	//const char* sfxVolumeValue = sfxVolumeSlider->GetValue() * 100;
	//App->renderer->DrawText(sfxVolumeValue, Vector2{ (SCREEN_WIDTH / 2) + (sfxVolumeSliderSize.x / 2) + OffsetTextToSliderX, (SCREEN_HEIGHT / 6) * 5.15f }, Vector2{ 0,0 }, App->assetLoader->agencyB, 60, 1, BLACK);

	App->renderer->UnlockRenderLayer();

	FadeRender();

	return true;
}

void SceneOptions::Exit()
{
	//Go to MainMenu or the Game Scene
	App->audio->PlayFx(App->assetLoader->audioMotorId);
	StartFadeIn(App->scene_main_menu, BLACK, 0.3f);
}

void SceneOptions::NextLanguage()
{
	arrowRightSettingsLanguageAnimator->SelectAnimation("arrowRightLanguageClick", false);
	ButtonAnimTimer.Start();
	hasClicked = true;

	languageIndex++;
	if (languageIndex > 2)
	{
		languageIndex = 0;
	}

	App->localization->ChangeLanguage((Language)languageIndex);

}

void SceneOptions::EnterNextLanguage()
{
	arrowRightSettingsLanguageAnimator->SelectAnimation("arrowRightLanguageOver", false);

	
}

void SceneOptions::PreviousLanguage()
{
	arrowLeftSettingsLanguageAnimator->SelectAnimation("arrowLeftLanguageClick", false);
	ButtonAnimTimer.Start();
	hasClicked = true;

	languageIndex--;
	if (languageIndex < 0)
	{
		languageIndex = 2;
	}

	App->localization->ChangeLanguage((Language)languageIndex);

}

void SceneOptions::EnterPreviousLanguage()
{
	arrowLeftSettingsLanguageAnimator->SelectAnimation("arrowLeftLanguageOver", false);

	
}

void SceneOptions::ExitLanguage()
{
	arrowLeftSettingsLanguageAnimator->SelectAnimation("arrowLeftLanguageIdle", false);
	arrowRightSettingsLanguageAnimator->SelectAnimation("arrowRightLanguageIdle", false);

	hasClicked = false;
}



