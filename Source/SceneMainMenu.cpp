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
	settings_buttonTexture_hover = App->texture->GetTexture("main_menu_settings");

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
	//delete play_button;

	//App->texture->DeleteTexture("main_menu_settings");
	//delete settings_button;

	return true;
}

void SceneMainMenu::ClickPlay()
{
	//this->StartFadeOut(BLACK, 1);
	this->StartFadeIn(App->scene_intro, BLACK, 1);
	// Go to Play Scene
}

void SceneMainMenu::ClickSettings()
{
	this->StartFadeIn(App->scene_options, BLACK, 1);
	// Go to Settings Scene
}

void SceneMainMenu::OnMouseOverPlay()
{
	ModuleRender::RenderLayer last_layer = App->renderer->GetCurrentRenderLayer();
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_5);

	App->renderer->Draw(*play_buttonTexture_hover, { play_buttonTextureRec.x + play_buttonTextureRec.width/2 , play_buttonTextureRec.y + play_buttonTextureRec.height/2 }, { 0,0 });

	App->renderer->SelectRenderLayer(last_layer);
}

void SceneMainMenu::OnMouseOverSettings()
{
	ModuleRender::RenderLayer last_layer = App->renderer->GetCurrentRenderLayer();
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_5);

	App->renderer->Draw(*settings_buttonTexture_hover, { settings_buttonTextureRec.x + settings_buttonTextureRec.width / 2 , settings_buttonTextureRec.y + settings_buttonTextureRec.height / 2 }, { 0,0 });

	App->renderer->SelectRenderLayer(last_layer);
}

update_status SceneMainMenu::Update()
{
	play_button->Update();
	settings_button->Update();

	App->renderer->Draw(*backgroundTexture, { backgroundTextureRec.x, backgroundTextureRec.y }, {0,0}, &backgroundTextureRec, 0, 2);
	play_button->Render();
	settings_button->Render();

	this->FadeUpdate();

	return UPDATE_CONTINUE;
}
