#pragma once
#include "GameMode.h"

#include <vector>

using namespace std;

class RaceMode : public GameMode
{
public:
	RaceMode(Application* app, bool start_enabled = true);
	~RaceMode();

	bool Init();
	update_status Update();
	bool CleanUp();

	int GetCurrentLapNum() const;
	void SetLapNum(int lapNum);

	double GetLapTimeSec(int lapNum) const;
	double GetCurrentLapTimeSec() const;

	void EndRace();

private:
	int currentLap = 0;
	Timer lapTimeCounter;
	
	int maxLapNum = 3;
	vector<double> lapTimes;

	// Temporal bools
	bool hasPlayerFinishedLap = false;
	bool timerStarted = false;

};

