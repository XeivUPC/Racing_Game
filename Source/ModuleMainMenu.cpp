#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleMainMenu.h"
#include "ModuleAudio.h"
#include "ModuleTexture.h"
#include "ModulePhysics.h"
#include "ModuleAssetLoader.h"

ModuleMainMenu::ModuleMainMenu(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{

}

ModuleMainMenu::~ModuleMainMenu()
{
}

bool ModuleMainMenu::Start()
{
	LOG("Loading Main Menu assets");
	bool ret = true;


	return ret;
}

bool ModuleMainMenu::CleanUp()
{
	LOG("Unloading Main Menu");

	return true;
}

update_status ModuleMainMenu::Update()
{
	return UPDATE_CONTINUE;
}
