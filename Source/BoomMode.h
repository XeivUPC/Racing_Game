#pragma once
#include "GameMode.h"

#include <vector>

using namespace std;

class BoomMode : public GameMode
{
public:
	BoomMode(Application* app, bool start_enabled = true);
	~BoomMode();

	bool Init();
	update_status Update();
	bool CleanUp();

	void ExplodePlayer();
	void ExplodeCPU();

	double GetTimeToExploadeSec() const;

	void EndRace();

private:
	int explosionTime = 60;
	Timer timeToExplode;

	// Temporal bools
	bool isPlayerLast = false;
	bool timerStarted = false;

};

