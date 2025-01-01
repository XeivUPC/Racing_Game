#include "RaceMode.h"

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
	if (IsRaceStarted() && !timerStarted) {
		lapTimeCounter.Start();
		timerStarted = true;
	}

	if (hasPlayerFinishedLap) {
		if (currentLap == maxLapNum) {
			EndRace();
		}
		else {
			SetLapNum(currentLap + 1);
		}
	}
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
	return lapTimes[lapNum];
}

double RaceMode::GetCurrentLapTimeSec() const
{
	return lapTimes[currentLap];
}

void RaceMode::EndRace()
{
	// Go to result scene
}
