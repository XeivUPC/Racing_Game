#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "SceneMainMenu.h"
#include "SceneSelectSetup.h"
#include "SceneOptions.h"
#include "ModuleAudio.h"
#include "ModuleTexture.h"
#include "ModuleAssetLoader.h"
#include "UIButton.h"
#include "ModuleLocalization.h"

SceneMainMenu::SceneMainMenu(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{
}

SceneMainMenu::~SceneMainMenu()
{
}

bool SceneMainMenu::Start()
{
	LOG("Loading Main Menu assets");
	bool ret = true;

	// Background
	App->texture->CreateTexture("Assets/Textures/main_menu.png", "main_menu");
	backgroundTexture = App->texture->GetTexture("main_menu");


	// Play Button
	// Texture
	App->texture->CreateTexture("Assets/Textures/main_menu_play_hover.png", "main_menu_play_hover");
	play_buttonTexture_hover = App->texture->GetTexture("main_menu_play_hover");
	
	//Functionality
	play_button = new UIButton(this, { play_buttonTextureRec.x, play_buttonTextureRec.y }, { play_buttonTextureRec.width, play_buttonTextureRec.height });
	
	play_button->onMouseClick.emplace_back([&]() {ClickPlay(); });
	play_button->onMouseOver.emplace_back([&]() {OnMouseOverPlay(); });

	// Settings Button
	//Texture
	App->texture->CreateTexture("Assets/Textures/main_menu_settings_hover.png", "main_menu_settings_hover");
	settings_buttonTexture_hover = App->texture->GetTexture("main_menu_settings_hover");

	//Functionality
	settings_button = new UIButton(this, { settings_buttonTextureRec.x, settings_buttonTextureRec.y }, { settings_buttonTextureRec.width, settings_buttonTextureRec.height });

	settings_button->onMouseClick.emplace_back([&]() {ClickSettings(); });
	settings_button->onMouseOver.emplace_back([&]() {OnMouseOverSettings(); });

	/* Create Audio */
	audioMotorId = App->audio->LoadFx("Assets/Sounds/Sfx/MotorSFX.wav");

	StartFadeOut(BLACK, 0.3f);

	return ret;
}

update_status SceneMainMenu::Update()
{
	play_button->Update();
	settings_button->Update();
	FadeUpdate();

	Render();
	return UPDATE_CONTINUE;
}

bool SceneMainMenu::Render() {

	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_3);
	App->renderer->Draw(*backgroundTexture, { backgroundTextureRec.x, backgroundTextureRec.y }, { 0,0 }, &backgroundTextureRec, 0, 2);

	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_4);
	App->renderer->BlockRenderLayer();
	if (App->localization->GetString("MAINMENU_PLAY").length() < 5) {
		App->renderer->DrawText(App->localization->GetString("MAINMENU_PLAY").c_str(), { play_buttonTextureRec.x , play_buttonTextureRec.y }, { buttonsText_Offset.x + App->assetLoader->titleFont.recs->width, buttonsText_Offset.y }, App->assetLoader->titleFont, 100, 0, WHITE);
	}
	else {
		App->renderer->DrawText(App->localization->GetString("MAINMENU_PLAY").c_str(), { play_buttonTextureRec.x , play_buttonTextureRec.y }, buttonsText_Offset, App->assetLoader->titleFont, 100, 0, WHITE);
	}

	App->renderer->DrawText(App->localization->GetString("MAINMENU_SETTINGS").c_str(), { settings_buttonTextureRec.x , settings_buttonTextureRec.y }, buttonsText_Offset, App->assetLoader->titleFont, 100, 0, WHITE);
	App->renderer->UnlockRenderLayer();

	FadeRender();

	return true;
}

bool SceneMainMenu::CleanUp()
{
	LOG("Unloading Main Menu");

	delete play_button;
	delete settings_button;

	return true;
}

void SceneMainMenu::ClickPlay()
{
	App->audio->PlayFx(audioMotorId);
	StartFadeIn(App->scene_select_setup, BLACK, 0.3f);
	// Go to Play Scene
}

void SceneMainMenu::ClickSettings()
{
	App->audio->PlayFx(audioMotorId);
	StartFadeIn(App->scene_options, BLACK, 0.3f);
	// Go to Options Scene
}

void SceneMainMenu::OnMouseOverPlay()
{
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_1);
	App->renderer->Draw(*play_buttonTexture_hover, { play_buttonTextureRec.x , play_buttonTextureRec.y }, { 0,0 }, &play_button_section, 0, 2);
}

void SceneMainMenu::OnMouseOverSettings()
{
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_1);
	App->renderer->Draw(*settings_buttonTexture_hover, { settings_buttonTextureRec.x , settings_buttonTextureRec.y }, { 0,0 }, &settings_button_section, 0, 2);
}