#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleAssetLoader.h"
#include "SceneGame.h"
#include "ModuleAudio.h"
#include "ModuleTexture.h"
#include "ModulePhysics.h"
#include "PauseMenu.h"

#include "Player.h"
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
	player = new Player(this);
	track = new RaceTrack(this, "Assets/Map/Map_2.tmx");

	StartFadeOut(WHITE, 0.5f);
	return ret;
}

// Load assets
bool SceneGame::CleanUp()
{
	LOG("Unloading Intro scene");
	player->CleanUp();
	delete player;
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
		player->Update();
		track->Update();
		App->renderer->camera.target = { (float)METERS_TO_PIXELS(player->GetVehiclePosition().x),(float)METERS_TO_PIXELS(player->GetVehiclePosition().y) };
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
	player->Render();
	pauseMenu->Render();
	ModuleScene::FadeRender();
	return true;
}
