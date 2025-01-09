#pragma once
#include "GameMode.h"

#include <vector>

class BoomMode : public GameMode
{
public:
	BoomMode(SceneGame* gameAt);
	~BoomMode();

	update_status Update();
	bool Render();
	bool CleanUp();

private:

	void ExplodePlayer();
	void ExplodeCPU();

	double GetTimeToExplodeSec() const;
	void SetTimeToExplodeSec(double time);

	void EndRace();

	int explosionTime = 5;
	Timer timeToExplode;
	Texture2D* setup = nullptr;

	int beepTime = 2;
	Timer beepTimer;

	int intenseBeepTime = 1;
	Timer intenseBeepTimer;

	// Temporal bools
	bool isPlayerLast = false;
	bool timerStarted = false;
	bool playerExploded = false;

	int explodedNum = 0;
};

