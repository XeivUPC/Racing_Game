#pragma once

#include "Globals.h"
#include "Timer.h"

class Application;

class GameMode
{
private:
	bool enabled;

	Timer totalRaceTime;
	Timer startCountdown;

	bool raceStarted = false;

public:
	Application* App;

	GameMode(Application* parent, bool start_enabled = true) : App(parent), enabled(start_enabled)
	{
	}

	virtual ~GameMode()
	{
	}

	bool IsEnabled() const
	{
		return enabled;
	}

	void Enable()
	{
		if (enabled == false)
		{
			enabled = true;
			Start();
		}
	}

	void Disable()
	{
		if (enabled == true)
		{
			enabled = false;
			CleanUp();
		}
	}

	virtual bool Init()
	{
		return true;
	}

	virtual bool Start()
	{
		if (startCountdown.ReadSec() == 5) {
			totalRaceTime.Start();
		}
		startCountdown.Start();
		return true;
	}

	virtual update_status PreUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update()
	{
		if (startCountdown.ReadSec() == 5) {
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

};