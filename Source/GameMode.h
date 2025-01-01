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
		startCountdown.Start();
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
		return UPDATE_CONTINUE;
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

	virtual void ExecuteFunction(std::string Id) {
		return;
	}
	
	virtual void ExecuteFunctionGivenInt(std::string Id, int input) {
		return;
	}

	virtual void ExecuteFunctionGivenDouble(std::string Id, double input) {
		return;
	}

	virtual double GetDoubleParameter(std::string Id) {
		return 0.0;
	}

	virtual double GetDoubleParameterGivenInt(std::string Id, int input) {
		return 0.0;
	}

	virtual int GetIntParameter(std::string Id) {
		return 0;
	}

};