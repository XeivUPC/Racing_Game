#include "RaceMode.h"
#include "Application.h"

RaceMode::RaceMode(Application* app, bool start_enabled) : GameMode (app, start_enabled)
{
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

	if (IsKeyPressed(KEY_L)) {
		hasPlayerFinishedLap = true;
	}

	App->renderer->SelectRenderLayer(App->renderer->OVER_LAYER_1);
	App->renderer->BlockRenderLayer();
	if (GetCountdownTime() >= 4 && GetCountdownTime() < 5 && !IsRaceStarted()) {
		App->renderer->DrawText(App->localization->FormatNumber(1, 0).c_str(), { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, { -MeasureTextEx(App->assetLoader->agencyB, App->localization->FormatNumber(1,0).c_str(), 80, 0).x / 2, -MeasureTextEx(App->assetLoader->agencyB, App->localization->FormatNumber(1,0).c_str(), 80, 0).y / 2 }, App->assetLoader->agencyB, 80, 0, WHITE);
	}
	else if (GetCountdownTime() >= 3 && GetCountdownTime() < 4 && !IsRaceStarted()) {
		App->renderer->DrawText(App->localization->FormatNumber(2, 0).c_str(), { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, { -MeasureTextEx(App->assetLoader->agencyB, App->localization->FormatNumber(2,0).c_str(), 80, 0).x / 2, -MeasureTextEx(App->assetLoader->agencyB, App->localization->FormatNumber(2,0).c_str(), 80, 0).y / 2 }, App->assetLoader->agencyB, 80, 0, WHITE);
	}
	else if (GetCountdownTime() >= 2 && GetCountdownTime() < 3 && !IsRaceStarted()) {
		App->renderer->DrawText(App->localization->FormatNumber(3, 0).c_str(), { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, { -MeasureTextEx(App->assetLoader->agencyB, App->localization->FormatNumber(3,0).c_str(), 80, 0).x / 2, -MeasureTextEx(App->assetLoader->agencyB, App->localization->FormatNumber(3,0).c_str(), 80, 0).y / 2 }, App->assetLoader->agencyB, 80, 0, WHITE);
	}

	if (IsRaceStarted() && !timerStarted) {
		lapTimeCounter.Start();
		timerStarted = true;
	}

	App->renderer->DrawText("Lap ", {0, 0}, { 0, 0 }, App->assetLoader->agencyB, 80, 0, WHITE);
	App->renderer->DrawText(App->localization->FormatNumber(currentLap, 0).c_str(), {0, 0}, { MeasureTextEx(App->assetLoader->agencyB, "Lap ", 80, 0).x, 0}, App->assetLoader->agencyB, 80, 0, WHITE);
	
	App->renderer->DrawText(App->localization->FormatNumber(GetCurrentLapTimeSec(), 0).c_str(), {0, 0}, {0, MeasureTextEx(App->assetLoader->agencyB, "Lap ", 80, 0).y + 10}, App->assetLoader->agencyB, 80, 0, WHITE);

	if (currentLap > 1) {
		App->renderer->DrawText(App->localization->FormatNumber(GetLapTimeSec(1), 0).c_str(), { 0, 0 }, { 0, MeasureTextEx(App->assetLoader->agencyB, "Lap ", 80, 0).y*2 + 10 }, App->assetLoader->agencyB, 80, 0, WHITE);
	}
	if (currentLap > 2) {
		App->renderer->DrawText(App->localization->FormatNumber(GetLapTimeSec(2), 0).c_str(), { 0, 0 }, { 0, MeasureTextEx(App->assetLoader->agencyB, "Lap ", 80, 0).y*3 + 10 }, App->assetLoader->agencyB, 80, 0, WHITE);
	}
	if (currentLap > 3) {
		App->renderer->DrawText(App->localization->FormatNumber(GetLapTimeSec(3), 0).c_str(), { 0, 0 }, { 0, MeasureTextEx(App->assetLoader->agencyB, "Lap ", 80, 0).y*4 + 10 }, App->assetLoader->agencyB, 80, 0, WHITE);
	}

	if (hasPlayerFinishedLap) {
		if (currentLap == maxLapNum) {
			EndRace();
		}
		else {
			SetLapNum(currentLap + 1);
		}
	}

	App->renderer->UnlockRenderLayer();
	return UPDATE_CONTINUE;
}

bool RaceMode::CleanUp()
{
	return false;
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
}
