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
	

	StartFadeOut(WHITE, 0.5f);
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
	car->Update();
	
	/// Last Things To Do
	ModuleScene::FadeUpdate();
	Render();
	return UPDATE_CONTINUE;
}

bool SceneGame::Render()
{
	car->Render();

	ModuleScene::FadeRender();
	return true;
}
