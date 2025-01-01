#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleAssetLoader.h"
#include "SceneGame.h"
#include "ModuleAudio.h"
#include "ModuleTexture.h"
#include "ModulePhysics.h"
#include "PauseMenu.h"
#include "RaceMode.h"
#include "BoomMode.h"

#include "Player.h"
#include "RaceTrack.h"
#include <raymath.h>


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
	track = new RaceTrack(this, trackPath);
	//mode = new RaceMode(App);
	mode = new BoomMode(App);

	mode->Start();

	StartFadeOut(WHITE, 0.5f);

	App->renderer->camera.zoom = 2;
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

	mode->CleanUp();
	delete mode;

	App->renderer->camera.target = {0,0};
	App->renderer->camera.offset = {0,0};
	App->renderer->camera.zoom = 1;
	return true;
}

void SceneGame::SetUpTrack(string path)
{
	trackPath = path;
}

// Update: draw background
update_status SceneGame::Update()
{
	if(!pauseMenu->IsPaused())
	{
		player->Update();
		track->Update();
		App->renderer->camera.target = player->GetVehiclePosition();
		App->renderer->camera.offset = { App->window->GetLogicWidth()/2.f,App->window->GetLogicHeight()/2.f};
		mode->Update();
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
