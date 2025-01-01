#pragma once
class Pilot;
class SceneGame;
class MapLapSensor;
class MapLapSensorController
{
private:
	SceneGame* game;
public:
	MapLapSensorController();
	~MapLapSensorController();
	void CrossCheckpoint(Pilot* pilot, int checkpointOrder);
};