#pragma once

#include "Globals.h"
#include "Timer.h"
#include "ModuleLocalization.h"
#include "ModuleRender.h"
#include "ModuleAssetLoader.h"

class SceneGame;

class GameMode
{
private:
	Timer totalRaceTime;
	Timer startCountdown;

	bool raceStarted = false;

public:
	SceneGame* gameAt;

	GameMode(SceneGame* gameAt) : gameAt(gameAt)
	{
		
	}

	virtual ~GameMode()
	{
	}

	virtual bool Init()
	{
		return true;
	}

	virtual bool Start()
	{
		startCountdown.Start();
		return true;
	}

	virtual update_status PreUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update()
	{
		if (startCountdown.ReadSec() >= 5 && !raceStarted) {
			totalRaceTime.Start();
			raceStarted = true;
		}

		totalRaceTime.Update();
		startCountdown.Update();

		return UPDATE_CONTINUE;
	}

	virtual bool Render()
	{
		return true;
	}

	virtual update_status PostUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp()
	{
		return true;
	}

	double GetTotalRaceTime() const
	{
		return totalRaceTime.ReadSec();
	}

	double GetCountdownTime() const
	{
		return startCountdown.ReadSec();
	}

	bool IsRaceStarted() const {
		return raceStarted;
	}

	virtual double GetBestLapTimeSec() const {
		return -1;
	}

	virtual int GetBestLapIndex() const {
		return 0;
	}

};