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

update_status RaceMode::PreUpdate()
{
	return update_status();
}

update_status RaceMode::Update()
{
	return update_status();
}

update_status RaceMode::PostUpdate()
{
	return update_status();
}

bool RaceMode::CleanUp()
{
	return false;
}

int RaceMode::GetLapNum() const
{
	return lapCounter;
}

double RaceMode::GetLapTimeSec(int lapNum) const
{
	return lapTimes[lapNum];
}
