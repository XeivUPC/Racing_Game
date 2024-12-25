#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "SceneMainMenu.h"
#include "SceneGame.h"
#include "ModuleAudio.h"
#include "ModuleTexture.h"
#include "ModuleAssetLoader.h"
#include "UIButton.h"
#include "SceneOptions.h"
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
	App->texture->CreateTexture("Assets/Textures/main_menu_play_size.png", "main_menu_play");
	play_buttonTexture = App->texture->GetTexture("main_menu_play");

	App->texture->CreateTexture("Assets/Textures/main_menu_play_hover_size.png", "main_menu_play_hover");
	play_buttonTexture_hover = App->texture->GetTexture("main_menu_play_hover");
	
	//Functionality
	play_button = new UIButton(this, { play_buttonTextureRec.x, play_buttonTextureRec.y }, { play_buttonTextureRec.width, play_buttonTextureRec.height }, play_buttonTexture);

	play_button->onMouseClick = [&]() {ClickPlay(); };
	play_button->onMouseOver = [&]() {OnMouseOverPlay(); };


	// Settings Button
	//Texture
	App->texture->CreateTexture("Assets/Textures/main_menu_settings_size.png", "main_menu_settings");
	settings_buttonTexture = App->texture->GetTexture("main_menu_settings");

	App->texture->CreateTexture("Assets/Textures/main_menu_settings_hover_size.png", "main_menu_settings_hover");
	settings_buttonTexture_hover = App->texture->GetTexture("main_menu_settings_hover");

	//Functionality
	settings_button = new UIButton(this, { settings_buttonTextureRec.x, settings_buttonTextureRec.y }, { settings_buttonTextureRec.width, settings_buttonTextureRec.height }, settings_buttonTexture);

	settings_button->onMouseClick = [&]() {ClickSettings(); };
	settings_button->onMouseOver = [&]() {OnMouseOverSettings(); };


	return ret;
}

bool SceneMainMenu::CleanUp()
{
	LOG("Unloading Main Menu");

	//App->texture->DeleteTexture("main_menu");

	//App->texture->DeleteTexture("main_menu_play");
	delete play_button;

	//App->texture->DeleteTexture("main_menu_settings");
	delete settings_button;

	return true;
}

void SceneMainMenu::ClickPlay()
{
	//this->StartFadeOut(BLACK, 1);
	this->StartFadeIn(App->scene_intro, BLACK, 0.3f);
	// Go to Play Scene
}

void SceneMainMenu::ClickSettings()
{
	this->StartFadeIn(App->scene_options, BLACK, 1);
	// Go to Settings Scene
}

void SceneMainMenu::OnMouseOverPlay()
{
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_1);
	App->renderer->Draw(*play_buttonTexture_hover, { play_buttonTextureRec.x , play_buttonTextureRec.y }, { 0,0 });
}

void SceneMainMenu::OnMouseOverSettings()
{
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_1);
	App->renderer->Draw(*settings_buttonTexture_hover, { settings_buttonTextureRec.x , settings_buttonTextureRec.y }, { 0,0 });
}

update_status SceneMainMenu::Update()
{
	play_button->Update();
	settings_button->Update();

	//App->renderer->UnlockRenderLayer();

	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_3);
	App->renderer->Draw(*backgroundTexture, { backgroundTextureRec.x, backgroundTextureRec.y }, {0,0}, &backgroundTextureRec, 0, 2);

	play_button->SelectElemRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_2);
	play_button->Render();
	settings_button->SelectElemRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_2);
	settings_button->Render();

	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_4);

	DrawTextEx(App->assetLoader->titleFont, App->localization->GetString("MAINMENU_PLAY").c_str(), { play_buttonTextureRec.x + 48 , play_buttonTextureRec.y }, 100, 0, WHITE);
	DrawTextEx(App->assetLoader->titleFont, App->localization->GetString("MAINMENU_SETTINGS").c_str(), { settings_buttonTextureRec.x + 48 , settings_buttonTextureRec.y }, 100, 0, WHITE);

	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_5);
	this->FadeUpdate();

	return UPDATE_CONTINUE;
}
