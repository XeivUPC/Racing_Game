#pragma once
#include "GameMode.h"

#include <vector>

class BoomMode : public GameMode
{
public:
	BoomMode(SceneGame* gameAt);
	~BoomMode();

	bool Init();
	update_status Update();
	bool Render();
	bool CleanUp();

	void ExecuteFunction(std::string Id) override;
	void ExecuteFunctionGivenDouble(std::string Id, double input) override;
	double GetDoubleParameter(std::string Id) override;



private:

	void ExplodePlayer();
	void ExplodeCPU();

	double GetTimeToExplodeSec() const;
	void SetTimeToExplodeSec(double time);

	void EndRace();

	int explosionTime = 5;
	Timer timeToExplode;

	int beepTime = 2;
	Timer beepTimer;

	int intenseBeepTime = 1;
	Timer intenseBeepTimer;

	// Temporal bools
	bool isPlayerLast = false;
	bool timerStarted = false;

	int explodedNum = 0;
};

