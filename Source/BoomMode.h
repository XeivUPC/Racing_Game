#pragma once
#include "GameMode.h"

#include <vector>

class BoomMode : public GameMode
{
public:
	BoomMode(Application* app, bool start_enabled = true);
	~BoomMode();

	bool Init();
	update_status Update();
	bool CleanUp();

	void ExecuteFunction(std::string Id) override;
	void ExecuteFunctionGivenDouble(std::string Id, double input) override;
	double GetDoubleParameter(std::string Id) override;

	void ExplodePlayer();
	void ExplodeCPU();

	double GetTimeToExplodeSec() const;
	void SetTimeToExplodeSec(double time);

	void EndRace();

private:
	int explosionTime = 60;
	Timer timeToExplode;

	// Temporal bools
	bool isPlayerLast = false;
	bool timerStarted = false;

};

