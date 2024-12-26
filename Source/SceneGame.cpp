#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleAssetLoader.h"
#include "SceneGame.h"
#include "ModuleAudio.h"
#include "ModuleTexture.h"
#include "ModulePhysics.h"

#include "Vehicle.h"


SceneGame::SceneGame(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{
	
}

SceneGame::~SceneGame()
{}

// Load assets
bool SceneGame::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	car = new Vehicle(this, "moto-type2");
	//// Aqui ponemos todos los chars de la funete en orden
	
	return ret;
}

// Load assets
bool SceneGame::CleanUp()
{
	LOG("Unloading Intro scene");
	car->CleanUp();
	delete car;
	return true;
}

// Update: draw background
update_status SceneGame::Update()
{
	slider->Update();
	car->Update();
	
	/// Last Things To Do
	ModuleScene::FadeUpdate();
	Render();
	return UPDATE_CONTINUE;
}

bool SceneGame::Render()
{
	car->Render();
	DrawTextEx(App->assetLoader->basicFont, "Hola que tal estas rey\nquedaste 3_-2", { 100, 100 }, 90, 1, BLACK);

	ModuleScene::FadeRender();
	return true;
}
