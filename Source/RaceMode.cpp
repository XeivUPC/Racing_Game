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
		SetLapNum(currentLap + 1);
		if (currentLap == maxLapNum) {
			EndRace();
		}
	}

	Application* App = gameAt->App;
	if (IsKeyPressed(KEY_N)) {
		App->scene_game->StartFadeIn(App->scene_results, BLACK, 0.3f);
	}

	lapTimeCounter.Update();
	return UPDATE_CONTINUE;
}

bool RaceMode::Render()
{
	Application* App = gameAt->App;
	App->renderer->SelectRenderLayer(App->renderer->SUB_LAYER_4);
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

		Color color1 = WHITE;
		Color color2 = WHITE;
		Color color3 = WHITE;

		switch (GetBestLapIndex())
		{
		case 1:
			color1 = GREEN;
			break;
		case 2:
			color2 = GREEN;
			break;
		case 3:
			color3 = GREEN;
			break;
		}

		if (currentLap > 1) {
			App->renderer->DrawText(App->localization->FormatNumber(GetLapTimeSec(1), 2).c_str(), { 0, 0 }, { 0, MeasureTextEx(App->assetLoader->agencyB, App->localization->FormatNumber(GetCurrentLapTimeSec(), 2).c_str() , 100, 0).y * 2 + 10 }, App->assetLoader->agencyB, 40, 0, color1);
		}
		if (currentLap > 2) {
			App->renderer->DrawText(App->localization->FormatNumber(GetLapTimeSec(2), 2).c_str(), { 0, 0 }, { 0, MeasureTextEx(App->assetLoader->agencyB, App->localization->FormatNumber(GetCurrentLapTimeSec(), 2).c_str() , 100, 0).y * 2 + 10 + MeasureTextEx(App->assetLoader->agencyB, App->localization->FormatNumber(GetCurrentLapTimeSec(), 2).c_str(), 40, 0).y }, App->assetLoader->agencyB, 40, 0, color2);
		}
		if (currentLap > 3) {
			App->renderer->DrawText(App->localization->FormatNumber(GetLapTimeSec(3), 2).c_str(), { 0, 0 }, { 0, MeasureTextEx(App->assetLoader->agencyB, App->localization->FormatNumber(GetCurrentLapTimeSec(), 2).c_str() , 100, 0).y * 2 + 10 + MeasureTextEx(App->assetLoader->agencyB, App->localization->FormatNumber(GetCurrentLapTimeSec(), 2).c_str(), 40, 0).y * 2 }, App->assetLoader->agencyB, 40, 0, color3);
		}

		int position = gameAt->GetRacePlayerPosition();
		string infoPosition = to_string(position)+"*";
		Vector2 posSize = MeasureTextEx(App->assetLoader->agencyB, infoPosition.c_str(), 100, 0);
		Color posColor = WHITE;
		switch (position)
		{
		case 1:
			posColor = GOLD;
			break;
		case 2:
			posColor = LIGHTGRAY;
			break;
		case 3:
			posColor = BROWN;
			break;
		default:
			break;
		}
		App->renderer->DrawText(infoPosition.c_str(), { 0,SCREEN_HEIGHT - posSize.y }, {0,0 }, App->assetLoader->agencyB, 120, 0, posColor);

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

double RaceMode::GetBestLapTimeSec() const
{
	if (lapTimes.empty()) {
		return 0;
	}
	double bestTime = std::numeric_limits<double>::max();
	for (double time : lapTimes) {
		if (time < bestTime) {
			bestTime = time;
		}
	}
	return bestTime;
}

int RaceMode::GetBestLapIndex() const
{
	if (lapTimes.empty()) {
		return 0;
	}
	double bestTime = std::numeric_limits<double>::max();
	int bestIndex = -1;
	for (size_t i = 0; i < lapTimes.size(); ++i) {
		if (lapTimes[i] < bestTime) {
			bestTime = lapTimes[i];
			bestIndex = static_cast<int>(i);
		}
	}
	return bestIndex + 1;
}

void RaceMode::EndRace()
{
	// Go to result scene
	Application* App = gameAt->App;
	App->scene_game->StartFadeIn(App->scene_results, BLACK, 0.3f);
}
