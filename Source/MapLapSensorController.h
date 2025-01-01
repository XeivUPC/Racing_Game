#pragma once
#include <vector>
class Pilot;
class SceneGame;
class MapLapSensor;
class MapLapSensorController
{
private:
	SceneGame* game;
public:
	MapLapSensorController(SceneGame* sgame);
	~MapLapSensorController();
	void CrossCheckpoint(Pilot* pilot, int checkpointOrder);
	bool CleanUp();
};