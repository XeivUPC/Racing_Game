#pragma once
#include "GameMode.h"

#include <vector>

class RaceMode : public GameMode
{
public:
	RaceMode(Application* app, bool start_enabled = true);
	~RaceMode();

	bool Init();
	update_status Update();
	bool CleanUp();

	void ExecuteFunction(std::string Id) override;
	void ExecuteFunctionGivenInt(std::string Id, int input) override;
	double GetDoubleParameter(std::string Id) override;
	double GetDoubleParameterGivenInt(std::string Id, int input) override;
	int GetIntParameter(std::string Id) override;

	int GetCurrentLapNum() const;
	void SetLapNum(int lapNum);

	double GetLapTimeSec(int lapNum) const;
	double GetCurrentLapTimeSec() const;

	void EndRace();

private:
	int currentLap = 1;
	Timer lapTimeCounter;
	
	int maxLapNum = 3;
	std::vector<double> lapTimes;

	// Temporal bools
	bool hasPlayerFinishedLap = false;
	bool timerStarted = false;

};

