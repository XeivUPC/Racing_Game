
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleTexture.h"
#include "ModuleLocalization.h"
#include "ModuleAssetLoader.h"
#include "ModulePhysics.h"
#include "SceneGame.h"
#include "SceneMainMenu.h"

#include "Application.h"

Application::Application()
{
	window = new ModuleWindow(this);
	renderer = new ModuleRender(this);
	audio = new ModuleAudio(this, true);
	texture = new ModuleTexture(this, true);
	localization = new ModuleLocalization(this, true);
	assetLoader = new ModuleAssetLoader(this);
	physics = new ModulePhysics(this);
	scene_intro = new SceneGame(this);
	scene_main_menu = new SceneMainMenu(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(physics);
	AddModule(audio);
	AddModule(texture);
	AddModule(localization);
	AddModule(assetLoader);
	
	// Scenes
	//AddModule(scene_intro);
	AddModule(scene_main_menu);

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

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	for (auto it = list_modules.rbegin(); it != list_modules.rend() && ret; ++it)
	{
		Module* item = *it;
		ret = item->CleanUp();
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.emplace_back(mod);
}