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
#include "UIRendererCPU.h"
#include "Vehicle.h"
#include "Pilot.h"
#include "PilotCPU.h"
#include "RaceTrack.h"
#include <raymath.h>
#include <algorithm>
#include <random>


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

	player = new Player(this, track, player_vehicle_type);
	pilots.emplace_back(player);

	cpuCharacterRenderer = new UIRendererCPU(this);

	vector<Vector2> startingPositions = track->GetTrackStartingPositions();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(1, vehicleTypeAmount);

	// Generate a random number
	
	for (int i = 0; i < 1; i++)
	{
		int randomNumber = distr(gen);
		pilots.emplace_back(new PilotCPU(this, track, vehicle_type+"type"+to_string(randomNumber)));
	}

	mode->Start();

	StartFadeOut(WHITE, 0.5f);

	App->renderer->camera.zoom = 2/track->GetScale();

	App->audio->PlayMusic("Assets/Sounds/Music/Race.wav");
	SetPilotsCharacters();
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

void SceneGame::SetPlayerVehicle(string type)
{
	player_vehicle_type = type;
}

void SceneGame::SetVehicleType(string type, int amount)
{
	vehicle_type = type;
	vehicleTypeAmount = amount;
}

void SceneGame::SetPlayerCharacter(int character)
{
	playerCharacter = character;
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

void SceneGame::SetPilotsCharacters()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::vector<int> characters = { 0,1,2,3,4,5,6,7 };
	characters.erase(characters.begin() + player->characterIndex);
	for each (Pilot* pilot in pilots)
	{
		std::uniform_int_distribution<> distr(0, characters.size()-1);
		if (pilot == player)
		{
			player->characterIndex = playerCharacter;
			continue;
		}
		int listIndex = distr(gen);
		pilot->characterIndex = characters[listIndex];
		characters.erase(characters.begin() + listIndex);
	}
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

	mode->Render();
	cpuCharacterRenderer->Render();
	pauseMenu->Render();
	ModuleScene::FadeRender();
	return true;
}
