#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleGame.h"
#include "ModuleAudio.h"
#include "ModuleTexture.h"
#include "ModulePhysics.h"
#include "ModuleAssetLoader.h"

#include "Vehicle.h"

ModuleGame::ModuleGame(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

ModuleGame::~ModuleGame()
{}

// Load assets
bool ModuleGame::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	car = new Vehicle(this, "moto-type2");

	return ret;
}

// Load assets
bool ModuleGame::CleanUp()
{
	LOG("Unloading Intro scene");
	car->CleanUp();
	delete car;
	return true;
}

// Update: draw background
update_status ModuleGame::Update()
{
	car->Update();
	return UPDATE_CONTINUE;
}
