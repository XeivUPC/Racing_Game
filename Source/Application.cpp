
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleTexture.h"
#include "ModuleLocalization.h"
#include "ModuleUserPreferences.h"
#include "ModuleAssetLoader.h"
#include "ModulePhysics.h"

#include "SceneResults.h"
#include "SceneGame.h"
#include "SceneOptions.h"
#include "SceneMainMenu.h"
#include "SceneSelectSetup.h"
#include "SceneVehicleSelectSetup.h"
#include "SceneIntro.h"

#include "Application.h"

Application::Application()
{
	window = new ModuleWindow(this);
	renderer = new ModuleRender(this);
	audio = new ModuleAudio(this, true);
	texture = new ModuleTexture(this, true);
	localization = new ModuleLocalization(this, true);
	userPrefs = new ModuleUserPreferences(this, true);
	assetLoader = new ModuleAssetLoader(this);
	physics = new ModulePhysics(this);
	scene_options = new SceneOptions(this);
	scene_game = new SceneGame(this, false);
	scene_results = new SceneResults(this, false);
	scene_select_setup = new SceneSelectSetup(this, false);
	scene_vehicle_select_setup = new SceneVehicleSelectSetup(this, false);
	scene_main_menu = new SceneMainMenu(this, false);
	scene_intro = new SceneIntro(this,true);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(physics);
	AddModule(audio);
	AddModule(texture);
	AddModule(localization);
	AddModule(userPrefs);
	AddModule(assetLoader);
	
	// Scenes
	AddModule(scene_results);
	AddModule(scene_game);
	AddModule(scene_select_setup);
	AddModule(scene_vehicle_select_setup);
	AddModule(scene_main_menu);
	AddModule(scene_intro);
	AddModule(scene_options);

	// Rendering happens at the end
	AddModule(renderer);
}

Application::~Application()
{
	for (auto it = list_modules.rbegin(); it != list_modules.rend(); ++it)
	{
		Module* item = *it;
		delete item;
	}
	list_modules.clear();
	
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	for (auto it = list_modules.begin(); it != list_modules.end() && ret; ++it)
	{
		Module* module = *it;
		ret = module->Init();
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");

	for (auto it = list_modules.begin(); it != list_modules.end() && ret; ++it)
	{
		Module* module = *it;
		if (module->IsEnabled())
			ret = module->Start();
	}
	
	return ret;
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (auto it = list_modules.begin(); it != list_modules.end() && ret == UPDATE_CONTINUE; ++it)
	{
		Module* module = *it;
		if (module->IsEnabled())
		{
			ret = module->PreUpdate();
		}
	}

	for (auto it = list_modules.begin(); it != list_modules.end() && ret == UPDATE_CONTINUE; ++it)
	{
		Module* module = *it;
		if (module->IsEnabled())
		{
			ret = module->Update();
		}
	}

	for (auto it = list_modules.begin(); it != list_modules.end() && ret == UPDATE_CONTINUE; ++it)
	{
		Module* module = *it;
		if (module->IsEnabled())
		{
			ret = module->PostUpdate();
		}
	}

	if (WindowShouldClose()) ret = UPDATE_STOP;


	ptimer.Update();
	startup_time.Update();
	frame_time.Update();
	last_sec_frame_time.Update();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	for (auto it = list_modules.rbegin(); it != list_modules.rend() && ret; ++it)
	{
		Module* item = *it;
		if(item->IsEnabled())
			ret = item->CleanUp();
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.emplace_back(mod);
}