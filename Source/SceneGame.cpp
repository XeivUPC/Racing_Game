#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleAssetLoader.h"
#include "SceneGame.h"
#include "ModuleAudio.h"
#include "ModuleTexture.h"
#include "ModulePhysics.h"
#include "PauseMenu.h"

#include "Vehicle.h"
#include "RaceTrack.h"


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
	//// Aqui ponemos todos los chars de la fuente en orden
	
	pauseMenu = new PauseMenu(this);
	pauseMenu->Start();
	car = new Vehicle(this, "car-type1");
	track = new RaceTrack(this, "Assets/Map/Map_2.tmx");

	StartFadeOut(WHITE, 0.5f);
	return ret;
}

// Load assets
bool SceneGame::CleanUp()
{
	LOG("Unloading Intro scene");
	car->CleanUp();
	delete car;
	pauseMenu->CleanUp();
	delete pauseMenu;

	track->CleanUp();
	delete track;
	return true;
}

// Update: draw background
update_status SceneGame::Update()
{
	if(pauseMenu)
	{
		car->Update();
		track->Update();
		App->renderer->camera.target = { (float)METERS_TO_PIXELS(car->GetPos().x),(float)METERS_TO_PIXELS(car->GetPos().y) };
		App->renderer->camera.offset = { GetScreenWidth()/2.f,GetScreenHeight()/2.f};
	}
	
	if (IsKeyPressed(KEY_P))
		pauseMenu->Pause();
	/// Last Things To Do
	Render();
	pauseMenu->Update();
	ModuleScene::FadeUpdate();
	return UPDATE_CONTINUE;
}

bool SceneGame::Render()
{
	track->Render();
	car->Render();
	pauseMenu->Render();
	ModuleScene::FadeRender();
	return true;
}
