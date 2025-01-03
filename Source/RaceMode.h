#pragma once
#include "GameMode.h"

#include <vector>

class RaceMode : public GameMode
{
public:
	RaceMode(SceneGame* gameAt, int NumberOfLaps);
	~RaceMode();

	bool Init();
	update_status Update();
	bool Render();
	bool CleanUp();

	void ExecuteFunction(std::string Id) override;
	void ExecuteFunctionGivenInt(std::string Id, int input) override;
	double GetDoubleParameter(std::string Id) override;
	double GetDoubleParameterGivenInt(std::string Id, int input) override;
	int GetIntParameter(std::string Id) override;

	

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

