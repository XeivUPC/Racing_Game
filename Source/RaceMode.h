#pragma once
#include "GameMode.h"

#include <vector>

class RaceMode : public GameMode
{
public:
	RaceMode(SceneGame* gameAt, int NumberOfLaps);
	~RaceMode();

	update_status Update();
	bool Render();
	bool CleanUp();

	double GetBestLapTimeSec() const;
	int GetBestLapIndex() const;

private:
	int GetCurrentLapNum() const;
	void SetLapNum(int lapNum);

	double GetLapTimeSec(int lapNum) const;
	double GetCurrentLapTimeSec() const;

	void EndRace();

	int currentLap = 1;
	Timer lapTimeCounter;

	int maxLapNum = 0;
	std::vector<double> lapTimes;

	// Temporal bools
	bool hasPlayerFinishedLap = false;
	bool timerStarted = false;

};

