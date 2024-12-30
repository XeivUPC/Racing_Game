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
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	int GetLapNum() const;
	//int SetLapNum();

	double GetLapTimeSec(int lapNum) const;


private:
	int lapCounter = 0;
	Timer lapTimeCounter;
	
	int maxLapNum = 3;
	vector<double> lapTimes;

};

