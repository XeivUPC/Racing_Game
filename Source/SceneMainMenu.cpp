#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "SceneMainMenu.h"
#include "ModuleAudio.h"
#include "ModuleTexture.h"
#include "ModuleAssetLoader.h"
#include "UIButton.h"

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

	App->texture->CreateTexture("Assets/Textures/main_menu", "main_menu");

	App->texture->CreateTexture("Assets/Textures/main_menu_play", "main_menu_play");
	play_button = new UIButton(this, { play_buttonTextureRec.x, play_buttonTextureRec.y }, { play_buttonTextureRec.width, play_buttonTextureRec.height }, App->texture->GetTexture("main_menu_play"));

	App->texture->CreateTexture("Assets/Textures/main_menu_settings", "main_menu_settings");
	settings_button = new UIButton(this, { settings_buttonTextureRec.x, settings_buttonTextureRec.y }, { settings_buttonTextureRec.width, settings_buttonTextureRec.height }, App->texture->GetTexture("main_menu_settings"));

	return ret;
}

bool SceneMainMenu::CleanUp()
{
	LOG("Unloading Main Menu");

	return true;
}

update_status SceneMainMenu::Update()
{

	App->renderer->Draw(*App->texture->GetTexture("main_menu"), { backgroundTextureRec.x, backgroundTextureRec.y },{0,0}/*, &backgroundTextureRec, 0, 2*/);

	return UPDATE_CONTINUE;
}
