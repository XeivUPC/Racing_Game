#pragma once
#include <vector>
class SceneGame;
class Pilot;
class MapLapSensorController
{
private:
	SceneGame* game;
	std::vector<Pilot*> pilotsInRace;
	void AddLap();
	void AddCheckpoint();
public:
	MapLapSensorController();
	~MapLapSensorController();
	void CrossCheckpoint(int checkpointOrder);
};