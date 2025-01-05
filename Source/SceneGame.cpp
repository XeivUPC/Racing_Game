#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleAssetLoader.h"
#include "SceneGame.h"
#include "ModuleAudio.h"
#include "ModuleTexture.h"
#include "ModulePhysics.h"
#include "MapLapSensor.h"
#include "PauseMenu.h"
#include "GameMode.h"
#include "Player.h"
#include "Vehicle.h"
#include "Pilot.h"
#include "PilotCPU.h"
#include "RaceTrack.h"
#include "Tree.h"
#include "Rock.h"

#include <raymath.h>
#include <algorithm>


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

	player = new Player(this, track, "car-type1");
	pilots.emplace_back(player);

	vector<Vector2> startingPositions = track->GetTrackStartingPositions();
	for (int i = 0; i < 1; i++)
	{
		pilots.emplace_back(new PilotCPU(this, track, "car-type1"));
	}

	mode->Start();

	tree = new Tree(this, {40,40});
	rock = new Rock(this, {60,60});

	StartFadeOut(WHITE, 0.5f);

	App->renderer->camera.zoom = 2/track->GetScale();

	App->audio->PlayMusic("Assets/Sounds/Music/Race.wav");
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

	tree->CleanUp();
	delete tree;

	rock->CleanUp();
	delete rock;

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

vector<Pilot*> SceneGame::GetRacePlacePositions() const
{
	vector<Pilot*> orderedPlacePositions = pilots;
	RaceTrack* trackRef = track;
	std::sort(orderedPlacePositions.begin(), orderedPlacePositions.end(), [trackRef](Pilot* a, Pilot* b) {
		if (a->CurrentLap() == b->CurrentLap()) {
			if (a->CurrentCheckpoint() == b->CurrentCheckpoint()) {
				int checkPointIndex = b->CurrentCheckpoint()+1;
				if (checkPointIndex >= trackRef->GetTrackSensors().size())
					checkPointIndex = 0;
				MapLapSensor* checkPoint = trackRef->GetTrackSensors()[checkPointIndex];
				float distanceA = Vector2Distance(a->vehicle->body->GetPosition(), checkPoint->GetCenter());
				float distanceB = Vector2Distance(b->vehicle->body->GetPosition(), checkPoint->GetCenter());
				return distanceA < distanceB;
			}
			else {
				return a->CurrentCheckpoint() > b->CurrentCheckpoint();
			}
		}
		return a->CurrentLap() > b->CurrentLap();
		});

	return orderedPlacePositions;
}

int SceneGame::GetRacePlayerPosition() const
{
	int position = -1;
	vector<Pilot*> pilots = GetRacePlacePositions();
	for (size_t i = 0; i < pilots.size(); i++)
	{
		if (pilots[i] == player) {
			position = i;
			break;
		}
	}
	return position + 1;
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
		else {
			vector<Vector2> startingPositions = track->GetTrackStartingPositions();
			for (int i = 0; i < pilots.size(); i++)
			{
				pilots[i]->vehicle->body->SetRotation(PI / 2.f);
				pilots[i]->vehicle->body->SetPosition(startingPositions[i].x, startingPositions[i].y);
			}
		}


		track->Update();

		tree->Update();
		rock->Update();

		App->renderer->camera.target =player->vehicle->body->GetPhysicPosition();
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

	tree->Render();
	mode->Render();
	pauseMenu->Render();
	ModuleScene::FadeRender();
	return true;
}
