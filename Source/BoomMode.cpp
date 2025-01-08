#include "BoomMode.h"
#include "Application.h"
#include "SceneGame.h"
#include "SceneResults.h"
#include "Player.h"
#include "Pilot.h"
#include "ModuleAudio.h"

BoomMode::BoomMode(SceneGame* gameAt) : GameMode(gameAt)
{
	beepTimer.Start();
	intenseBeepTimer.Start();
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

	if (gameAt->GetRacePlayerPosition() == gameAt->GetRacePlacePositions().size() - (explodedNum)) {
		isPlayerLast = true;
		if (explodedNum == 7) {
			EndRace();
		}
	}
	else {
		isPlayerLast = false;
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

	Application* App = gameAt->App;
	if (IsKeyPressed(KEY_N)) {
		App->scene_game->StartFadeIn(App->scene_results, BLACK, 0.3f);
	}
	if (isPlayerLast)
	{
		if (intenseBeepTimer.ReadSec() > intenseBeepTime && timeToExplode.ReadSec() > explosionTime + 5)
		{
			gameAt->App->audio->PlayFx(gameAt->App->assetLoader->audioBombCountdownBeepId, true);
			intenseBeepTimer.Start();
		}
		else if (beepTimer.ReadSec() > beepTime)
		{
			gameAt->App->audio->PlayFx(gameAt->App->assetLoader->audioBombCountdownBeepId, true);
			beepTimer.Start();
		}
	}
	
	timeToExplode.Update();
	beepTimer.Update();
	intenseBeepTimer.Update();

	return UPDATE_CONTINUE;
}

bool BoomMode::Render()
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

	if (IsRaceStarted()) {
		App->renderer->DrawText(App->localization->GetString("BOOMMODE_TIME_TILL_EXPLOSION").c_str(), { 0, 0 }, { 0, 0 }, App->assetLoader->agencyB, 80, 0, WHITE);
		App->renderer->DrawText(App->localization->FormatNumber(explosionTime - (float)timeToExplode.ReadSec(), 0).c_str(), { 0, 0 }, { MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("BOOMMODE_TIME_TILL_EXPLOSION").c_str(), 80, 0).x, 0 }, App->assetLoader->agencyB, 80, 0, WHITE);

		if (isPlayerLast) {
			App->renderer->DrawText(App->localization->GetString("BOOMMODE_LAST").c_str(), { 0, 0 }, { 0, MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("BOOMMODE_TIME_TILL_EXPLOSION").c_str(), 80, 0).y + 10 }, App->assetLoader->agencyB, 40, 0, WHITE);
		}


		int position = gameAt->GetRacePlayerPosition();
		string infoPosition = to_string(position) + "/" + to_string(gameAt->pilots.size());
		Vector2 posSize = MeasureTextEx(App->assetLoader->agencyB, infoPosition.c_str(), 100, 0);
		App->renderer->DrawText(infoPosition.c_str(), { 0,SCREEN_HEIGHT - posSize.y }, { 0,0 }, App->assetLoader->agencyB, 120, 0, WHITE);

	}
	App->renderer->UnlockRenderLayer();

	return true;
}

bool BoomMode::CleanUp()
{
	return false;
}

void BoomMode::ExplodePlayer()
{
	// Explode player's car and loose
	gameAt->App->audio->PlayFx(gameAt->App->assetLoader->audioExplosionId, true);
	auto& racePositions = gameAt->GetRacePlacePositions();
	size_t startPosition = racePositions.size() - (explodedNum + 1);

	for (size_t i = startPosition; i < racePositions.size(); ++i) {
		racePositions.at(i)->BeginExplosion();
	}
	EndRace();
}

void BoomMode::ExplodeCPU()
{
	// Explode CPU's car
	timeToExplode.Start();
	gameAt->App->audio->PlayFx(gameAt->App->assetLoader->audioExplosionId, true);
	auto& racePositions = gameAt->GetRacePlacePositions();
	size_t startPosition = racePositions.size() - (explodedNum + 1);

	for (size_t i = startPosition; i < racePositions.size(); ++i) {
		racePositions.at(i)->BeginExplosion();
	}
	explodedNum++;
}

double BoomMode::GetTimeToExplodeSec() const
{
	return timeToExplode.ReadSec();
}

void BoomMode::SetTimeToExplodeSec(double time)
{
	explosionTime = (int)time;
}

void BoomMode::EndRace()
{
	// Go to results
	Application* App = gameAt->App;
	App->scene_game->StartFadeIn(App->scene_results, BLACK, 0.3f);
}
