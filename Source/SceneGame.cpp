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
#include "GameMode.h"
#include "Player.h"
#include "Pilot.h"
#include "PilotCPU.h"
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

	track = new RaceTrack(this, trackPath);

	player = new Player(this, "car-type1");
	pilots.emplace_back(player);

	vector<Vector2> startingPositions = track->GetTrackStartingPositions();
	for (int i = 0; i < (int)startingPositions.size() - 1; i++)
	{
		pilots.emplace_back(new PilotCPU(this, "car-type3"));
	}

	for (int i = 0; i < (int)startingPositions.size(); i++)
	{
		pilots[i]->SetVehiclePosition(startingPositions[i]);
		pilots[i]->SetVehicleRotation(PI/2.f);
	}


	mode->Start();

	StartFadeOut(WHITE, 0.5f);

	App->renderer->camera.zoom = 2/track->GetScale();
	return ret;
}

// Load assets
bool SceneGame::CleanUp()
{
	LOG("Unloading Intro scene");

	player = nullptr;
	for (const auto& pilot : pilots) {
		pilot->CleanUp();
		delete pilot;
	}
	pilots.clear();

	pauseMenu->CleanUp();
	delete pauseMenu;

	track->CleanUp();
	delete track;

	mode->CleanUp();
	delete mode;

	App->renderer->camera.target = { 0,0 };
	App->renderer->camera.offset = { 0,0 };
	App->renderer->camera.zoom = 1;
	return true;
}

void SceneGame::SetUpTrack(string path)
{
	trackPath = path;
}

void SceneGame::SetMode(GameMode* mode)
{
	this->mode = mode;
}

// Update: draw background
update_status SceneGame::Update()
{
	if (!pauseMenu->IsPaused())
	{
		if (mode->IsRaceStarted()) {
			for (const auto& pilot : pilots) {
				pilot->Update();
			}
		}


		track->Update();
		App->renderer->camera.target = player->GetVehiclePosition();
		App->renderer->camera.offset = { App->window->GetLogicWidth() / 2.f,App->window->GetLogicHeight() / 2.f };
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
	for (const auto& pilot : pilots) {
		pilot->Render();
	}
	pauseMenu->Render();
	ModuleScene::FadeRender();
	return true;
}
