#include "RaceMode.h"
#include "Application.h"
#include "SceneGame.h"
#include "SceneResults.h"
#include "Player.h"

RaceMode::RaceMode(SceneGame* gameAt, int NumberOfLaps) : GameMode (gameAt)
{
	maxLapNum = NumberOfLaps + 1;
}

RaceMode::~RaceMode()
{
}

bool RaceMode::Init()
{
	return false;
}

update_status RaceMode::Update()
{
	GameMode::Update();

	if(gameAt->player->CurrentLap()+1!= currentLap)
	{
		hasPlayerFinishedLap = true;
	}

	if (hasPlayerFinishedLap) {
		if (currentLap == maxLapNum) {
			EndRace();
		}
		else {
			SetLapNum(currentLap + 1);
		}
	}

	Application* App = gameAt->App;
	if (IsKeyPressed(KEY_N)) {
		App->scene_game->StartFadeIn(App->scene_results, BLACK, 0.3f);
	}

	Render();
	return UPDATE_CONTINUE;
}

bool RaceMode::Render()
{
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

	if (IsRaceStarted() && !timerStarted) {
		lapTimeCounter.Start();
		timerStarted = true;
	}
	if (IsRaceStarted()) {
		if (currentLap != maxLapNum) {
			App->renderer->DrawText(App->localization->GetString("RACEMODE_LAP").c_str(), {0, 0}, {0, 0}, App->assetLoader->agencyB, 80, 0, WHITE);
			App->renderer->DrawText(App->localization->FormatNumber(currentLap, 0).c_str(), { 0, 0 }, { MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("RACEMODE_LAP").c_str(), 80, 0).x, 0 }, App->assetLoader->agencyB, 80, 0, WHITE);

			App->renderer->DrawText(App->localization->FormatNumber(GetCurrentLapTimeSec(), 2).c_str(), { 0, 0 }, { 0, MeasureTextEx(App->assetLoader->agencyB, App->localization->FormatNumber(GetCurrentLapTimeSec(), 2).c_str() , 80, 0).y + 10 }, App->assetLoader->agencyB, 70, 0, WHITE);
		}
		else {
			App->renderer->DrawText("Race ended :D Omedeto! ", { 0, 0 }, { 0, 0 }, App->assetLoader->agencyB, 80, 0, WHITE);
		}

		if (currentLap > 1) {
			App->renderer->DrawText(App->localization->FormatNumber(GetLapTimeSec(1), 2).c_str(), { 0, 0 }, { 0, MeasureTextEx(App->assetLoader->agencyB, App->localization->FormatNumber(GetCurrentLapTimeSec(), 2).c_str() , 100, 0).y * 2 + 10 }, App->assetLoader->agencyB, 40, 0, WHITE);
		}
		if (currentLap > 2) {
			App->renderer->DrawText(App->localization->FormatNumber(GetLapTimeSec(2), 2).c_str(), { 0, 0 }, { 0, MeasureTextEx(App->assetLoader->agencyB, App->localization->FormatNumber(GetCurrentLapTimeSec(), 2).c_str() , 100, 0).y * 2 + 10 + MeasureTextEx(App->assetLoader->agencyB, App->localization->FormatNumber(GetCurrentLapTimeSec(), 2).c_str(), 40, 0).y }, App->assetLoader->agencyB, 40, 0, WHITE);
		}
		if (currentLap > 3) {
			App->renderer->DrawText(App->localization->FormatNumber(GetLapTimeSec(3), 2).c_str(), { 0, 0 }, { 0, MeasureTextEx(App->assetLoader->agencyB, App->localization->FormatNumber(GetCurrentLapTimeSec(), 2).c_str() , 100, 0).y * 2 + 10 + MeasureTextEx(App->assetLoader->agencyB, App->localization->FormatNumber(GetCurrentLapTimeSec(), 2).c_str(), 40, 0).y * 2 }, App->assetLoader->agencyB, 40, 0, WHITE);
		}
	}
	App->renderer->UnlockRenderLayer();
	return true;
}

bool RaceMode::CleanUp()
{
	return false;
}

void RaceMode::ExecuteFunction(std::string Id)
{
	if (Id.c_str() == "EndRace") {
		EndRace();
	}
	else {
		return;
	}
}

void RaceMode::ExecuteFunctionGivenInt(std::string Id, int input)
{
	if (Id.c_str() == "SetLapNum") {
		SetLapNum(input);
	}
	else {
		return;
	}
}

double RaceMode::GetDoubleParameter(std::string Id)
{
	if (Id.c_str() == "GetCurrentLapTimeSec") {
		return GetCurrentLapTimeSec();
	}
	else {
		return 0.0;
	}
}

double RaceMode::GetDoubleParameterGivenInt(std::string Id, int input)
{
	if (Id.c_str() == "GetLapTimeSec") {
		return GetLapTimeSec(input);
	}
	else {
		return 0.0;
	}
}

int RaceMode::GetIntParameter(std::string Id)
{
	if (Id.c_str() == "GetCurrentLapNum") {
		return GetCurrentLapNum();
	}
	else {
		return 0;
	}
}

int RaceMode::GetCurrentLapNum() const
{
	return currentLap;
}

void RaceMode::SetLapNum(int lapNum)
{
	currentLap = lapNum;
	lapTimes.emplace_back(lapTimeCounter.ReadSec());
	lapTimeCounter.Start();
	hasPlayerFinishedLap = false;
}

double RaceMode::GetLapTimeSec(int lapNum) const
{
	return lapTimes[lapNum-1];
}

double RaceMode::GetCurrentLapTimeSec() const
{
	return lapTimeCounter.ReadSec();
}

void RaceMode::EndRace()
{
	// Go to result scene
	Application* App = gameAt->App;
	App->scene_game->StartFadeIn(App->scene_results, BLACK, 0.3f);
}
