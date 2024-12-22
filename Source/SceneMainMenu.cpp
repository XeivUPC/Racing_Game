#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "SceneMainMenu.h"
#include "ModuleAudio.h"
#include "ModuleTexture.h"
#include "ModulePhysics.h"
#include "ModuleAssetLoader.h"

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


	return ret;
}

bool SceneMainMenu::CleanUp()
{
	LOG("Unloading Main Menu");

	return true;
}

update_status SceneMainMenu::Update()
{
	return UPDATE_CONTINUE;
}
