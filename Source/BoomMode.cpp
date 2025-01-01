#include "BoomMode.h"
#include "Application.h"
#include "SceneGame.h"
#include "Player.h"

BoomMode::BoomMode(SceneGame* gameAt) : GameMode(gameAt)
{
}

BoomMode::~BoomMode()
{
}

bool BoomMode::Init()
{
	return false;
}

update_status BoomMode::Update()
{
	GameMode::Update();

	if (IsKeyPressed(KEY_E)) {
		isPlayerLast = !isPlayerLast;
	}

	Application* App = gameAt->App;

	App->renderer->SelectRenderLayer(App->renderer->OVER_LAYER_1);
	App->renderer->BlockRenderLayer();
	if (GetCountdownTime() >= 4 && GetCountdownTime() < 5 && !IsRaceStarted()) {
		App->renderer->DrawText(App->localization->FormatNumber(1, 0).c_str(), { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, { -MeasureTextEx(App->assetLoader->agencyB, App->localization->FormatNumber(1,0).c_str(), 120, 0).x / 2, -MeasureTextEx(App->assetLoader->agencyB, App->localization->FormatNumber(1,0).c_str(), 120, 0).y / 2 }, App->assetLoader->agencyB, 120, 0, WHITE);
	}
	else if (GetCountdownTime() >= 3 && GetCountdownTime() < 4 && !IsRaceStarted()) {
		App->renderer->DrawText(App->localization->FormatNumber(2, 0).c_str(), { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, { -MeasureTextEx(App->assetLoader->agencyB, App->localization->FormatNumber(2,0).c_str(), 120, 0).x / 2, -MeasureTextEx(App->assetLoader->agencyB, App->localization->FormatNumber(2,0).c_str(), 120, 0).y / 2 }, App->assetLoader->agencyB, 120, 0, WHITE);
	}
	else if (GetCountdownTime() >= 2 && GetCountdownTime() < 3 && !IsRaceStarted()) {
		App->renderer->DrawText(App->localization->FormatNumber(3, 0).c_str(), { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, { -MeasureTextEx(App->assetLoader->agencyB, App->localization->FormatNumber(3,0).c_str(), 120, 0).x / 2, -MeasureTextEx(App->assetLoader->agencyB, App->localization->FormatNumber(3,0).c_str(), 120, 0).y / 2 }, App->assetLoader->agencyB, 120, 0, WHITE);
	}

	if (IsRaceStarted()) {
		App->renderer->DrawText("Time to explode: ", { 0, 0 }, { 0, 0 }, App->assetLoader->agencyB, 80, 0, WHITE);
		App->renderer->DrawText(App->localization->FormatNumber(explosionTime - timeToExplode.ReadSec(), 0).c_str(), {0, 0}, {MeasureTextEx(App->assetLoader->agencyB, "Time to explode: ", 80, 0).x, 0}, App->assetLoader->agencyB, 80, 0, WHITE);

		App->renderer->DrawText("Is player last: ", {0, 0}, {0, MeasureTextEx(App->assetLoader->agencyB, "Time to explode: ", 80, 0).y + 10}, App->assetLoader->agencyB, 80, 0, WHITE);
	
		if (isPlayerLast) {
			App->renderer->DrawText("Yes", {0, 0}, {MeasureTextEx(App->assetLoader->agencyB, "Is player last? ", 80, 0).x, MeasureTextEx(App->assetLoader->agencyB, "Is player last? ", 80, 0).y + 10 }, App->assetLoader->agencyB, 80, 0, WHITE);
		}
		else {
			App->renderer->DrawText("No", {0, 0}, {MeasureTextEx(App->assetLoader->agencyB, "Is player last? ", 80, 0).x, MeasureTextEx(App->assetLoader->agencyB, "Is player last? ", 80, 0).y + 10 }, App->assetLoader->agencyB, 80, 0, WHITE);
		}
	}
	

	if (IsRaceStarted() && !timerStarted) {
		timeToExplode.Start();
		timerStarted = true;
	}

	if (timeToExplode.ReadSec() > explosionTime) {
		if (isPlayerLast) {
			ExplodePlayer();
		}
		else {
			ExplodeCPU();
		}
	}

	return UPDATE_CONTINUE;
}

bool BoomMode::CleanUp()
{
	return false;
}

void BoomMode::ExecuteFunction(std::string Id)
{
	if (Id.c_str() == "ExplodePlayer") {
		ExplodePlayer();
	}
	else if (Id.c_str() == "ExplodeCPU") {
		ExplodeCPU();
	}
	else if (Id.c_str() == "EndRace") {
		EndRace();
	}
	else {
		return;
	}
}

void BoomMode::ExecuteFunctionGivenDouble(std::string Id, double input)
{
	if (Id.c_str() == "SetTimeToExplodeSec") {
		SetTimeToExplodeSec(input);
	}
	else {
		return;
	}
}

double BoomMode::GetDoubleParameter(std::string Id)
{
	if (Id.c_str() == "GetTimeToExplodeSec") {
		return GetTimeToExplodeSec();
	}
	else {
		return 0.0;
	}
}

void BoomMode::ExplodePlayer()
{
	// Explode player's car and loose
	gameAt->App->renderer->DrawText("BOOOOOM!!", { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, { -MeasureTextEx(gameAt->App->assetLoader->agencyB, "BOOOOOM!!", 160, 0).x / 2, -MeasureTextEx(gameAt->App->assetLoader->agencyB, "BOOOOOM!!", 120, 0).y / 2}, gameAt->App->assetLoader->agencyB, 160, 0, WHITE);
	EndRace();
}

void BoomMode::ExplodeCPU()
{
	// Explode CPU's car
	timeToExplode.Start();
}

double BoomMode::GetTimeToExplodeSec() const
{
	return timeToExplode.ReadSec();
}

void BoomMode::SetTimeToExplodeSec(double time)
{
	explosionTime = time;
}

void BoomMode::EndRace()
{
	// Go to results
}
