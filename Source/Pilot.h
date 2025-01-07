#pragma once
#include <string>
#include "MapObject.h"

class SceneGame;
class Vehicle;
struct Vector2;
class RaceTrack;

class Pilot : public MapObject
{
protected:
	int lap=0;
	int checkpoint=0;
	RaceTrack* track;
	SceneGame* gameAt;
	std::string pilotName = "The Unamed";
public:
	Pilot(SceneGame* gameAt, RaceTrack* track, std::string vehicleType);
	~Pilot();
	bool Start();
	update_status Update();
	bool Render();
	bool CleanUp();

	void AddLap();
	void AddCheckpoint();
	int CurrentCheckpoint();
	int CurrentLap();
	std::string GetPilotName();
	Vehicle* vehicle;
};