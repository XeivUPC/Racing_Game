#include "BoomMode.h"

BoomMode::BoomMode(Application* app, bool start_enabled) : GameMode(app, start_enabled)
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

void BoomMode::ExplodePlayer()
{
	// Explode player's car and loose
	EndRace();
}

void BoomMode::ExplodeCPU()
{
	// Explode CPU's car
	timeToExplode.Start();
}

double BoomMode::GetTimeToExploadeSec() const
{
	return timeToExplode.ReadSec();
}

void BoomMode::EndRace()
{
	// Go to results
}
